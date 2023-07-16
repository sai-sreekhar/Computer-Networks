BEGIN {
    receivedCount = 0;
    sentCount = 0;
}

{
    event = $1
    if (event == "r") {
        receivedCount++;
    }
    if(event == "s"){
        sentCount++;
    }
}

END {
    printf("ReceivedCount: %i\tSentCount: %i\t\n", receivedCount, sentCount);
}
