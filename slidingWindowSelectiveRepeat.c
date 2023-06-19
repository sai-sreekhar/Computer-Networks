#include <stdio.h>

#define MAX_FRAMES 50

int main()
{
    int windowSize, numFrames, frames[MAX_FRAMES], ack[MAX_FRAMES] = {0};
    int currentFrameIndex, windowStartIndex, windowEndIndex;

    printf("Enter window size: ");
    scanf("%d", &windowSize);

    printf("Enter the number of frames to transmit: ");
    scanf("%d", &numFrames);

    printf("Enter %d frames: ", numFrames);

    // Input the frames
    for (currentFrameIndex = 0; currentFrameIndex < numFrames; currentFrameIndex++)
    {
        scanf("%d", &frames[currentFrameIndex]);
    }

    printf("\nWith Selective Repeat protocol, the frames will be sent in the following manner:\n\n");

    // Process the frames using Selective Repeat protocol
    for (windowStartIndex = 0; windowStartIndex < numFrames; windowStartIndex += windowSize)
    {
        windowEndIndex = windowStartIndex + windowSize;

        // Ensure the window doesn't exceed the total number of frames
        if (windowEndIndex > numFrames)
        {
            windowEndIndex = numFrames;
        }

        // Send the frames within the window
        for (currentFrameIndex = windowStartIndex; currentFrameIndex < windowEndIndex; currentFrameIndex++)
        {
            printf("Sending frame %d\n", frames[currentFrameIndex]);
        }

        // Receive acknowledgments for the frames within the window
        for (currentFrameIndex = windowStartIndex; currentFrameIndex < windowEndIndex; currentFrameIndex++)
        {
            int shouldResend = 0;

            printf("Acknowledgement for frame %d: ", frames[currentFrameIndex]);
            scanf("%d", &ack[currentFrameIndex]);

            if (ack[currentFrameIndex] == 0)
            {
                printf("Frame %d is lost. Resending...\n", frames[currentFrameIndex]);
                shouldResend = 1;
            }
            else
            {
                printf("Acknowledgement received for frame %d\n", frames[currentFrameIndex]);
            }

            // Resend the frame if required
            if (shouldResend)
            {
                printf("Resending frame %d\n", frames[currentFrameIndex]);
                printf("Acknowledgement for frame %d: ", frames[currentFrameIndex]);
                scanf("%d", &ack[currentFrameIndex]);

                if (ack[currentFrameIndex] == 0)
                {
                    printf("Frame %d is lost again.\n", frames[currentFrameIndex]);
                }
                else
                {
                    printf("Acknowledgement received for frame %d\n", frames[currentFrameIndex]);
                }
            }
        }

        // Check if any frames within the window were not acknowledged
        for (currentFrameIndex = windowStartIndex; currentFrameIndex < windowEndIndex; currentFrameIndex++)
        {
            if (ack[currentFrameIndex] == 0)
            {
                printf("Frame %d not acknowledged. Resending the entire window...\n", frames[currentFrameIndex]);
                windowStartIndex = currentFrameIndex;
                break;
            }
        }
    }

    return 0;
}
