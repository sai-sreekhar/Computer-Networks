#include <iostream>
#include <string>

using namespace std;
string bitwiseXOR(string a, string b)
{
    string result = "";
    int n = b.length();
    for (int i =1; i < n; i++)
    {
        if (a[i] == b[i])
            result += "0";
        else
            result += "1";
    }
    return result;
}


string modulo2Division(string dividend, string divisor)
{
    int pick = divisor.length();

    string tmp = dividend.substr(0, pick);

    int n = dividend.length();
    while (pick < n)
    {
        if (tmp[0] == '1')
            tmp = bitwiseXOR(divisor, tmp) + dividend[pick];
        else
            tmp = bitwiseXOR(string(pick, '0'), tmp) +
                  dividend[pick];
        pick +=
            1;

    }
    if (tmp[0] == '1')
        tmp = bitwiseXOR(divisor, tmp);
    else
        tmp = bitwiseXOR(string(pick, '0'), tmp);
    return tmp;
}

void encodeData(string data, string key)
{
    int keyLength = key.length();
    string appendedData = (data + string(keyLength -
                                         1, '0'));
    string remainder = modulo2Division(appendedData, key);
    string codeword = data + remainder;
    cout << "Remainder: " << remainder << "\n";
    cout << "Encoded Data (Data + Remainder): " << codeword << "\n";
}

void receiver(string data, string key)
{
    string currentXOR = modulo2Division(data.substr(
                                            0, key.size()),
                                        key);
    int current = key.size();
    while (current != data.size())
    {
        if (currentXOR.size() != key.size())
        {
            currentXOR.push_back(data[current++]);
        }
        else
        {
            currentXOR = modulo2Division(currentXOR, key);
        }
    }
    if (currentXOR.size() == key.size())
    {
        currentXOR = modulo2Division(currentXOR, key);
    }
    if (currentXOR.find('1') != string::npos)
    {
        cout << "There is an error in the received data.\n";
    }
    else
    {
        cout << "Correct message received.\n";
    }
}
int main()
{
    string dataToSend;
    cout << "Enter the data to be sent: ";
    cin >> dataToSend;
    string senderKey;
    cout << "Enter the key at the sender side: ";
    cin >> senderKey;
    string receivedData;
    cout << "Enter the received data: ";
    cin >> receivedData;
    string receiverKey;
    cout << "Enter the key at the receiver side: ";
    cin >> receiverKey;
    cout << "--------------------Sender side--------------------\n";
    cout << "Data to be sent: " << dataToSend << "\n";
    cout << "Key: " << senderKey << "\n";
    encodeData(dataToSend, senderKey);
    cout << "--------------------Receiver side--------------------\n";
    cout << "Received data: " << receivedData << "\n";
    cout << "Key: " << receiverKey << "\n";
    receiver(receivedData, receiverKey);
    return 0;
}