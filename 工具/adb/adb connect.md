## adb connect

use ADB over Wi-Fi

### adb connect <host>[:<port>]

STEP 1.

Connect to the device over USB.

STEP 2.

```
adb devices
```

List of devices attached
\######## device

Notes: STEP 1,2 is required

STEP 3.

```
adb tcpip 5555
```

restarting in TCP mode port: 5555

STEP 4.

Find out the IP address of the Android device: Settings -> About -> Status -> IP address. Remember the IP address, of the form #.#.#.#.

STEP 5.

```
adb connect #.#.#.#
```

connected to #.#.#.#:5555

STEP 6.

Remove USB cable from device, and confirm you can still access device:

```
adb devices
```