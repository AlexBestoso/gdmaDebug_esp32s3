# gdmaDebug_esp32s3
Class for troubleshooting the DMA registers on the ESP32s3

## work in progress
This branch is being used to integrate Permission Controls so that we can actually configure DMA using the most up to date libraries.

The esp32s3 GDMA interface appears to require that the permission control system is interacted with, as it involves directly accessing memory.<br>
So for the time being this repo is on hold until I figure out how to use permission controls.
