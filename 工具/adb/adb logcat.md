## adb logcat

Prints log data to the screen

abd logcat \[option]\[filter-specs]

```C++
adb logcat
```

```C++
adb logcat *:V //lowest priority, filter to only show verbose level
adb logcat *:D //filter to only show info level
adb logcat *:I //filtert to only show debug level
adb logcat *:W //filter to only show Warning level
adb logcat *:E //filter to only show Error level
adb logcat *:F //filter to only show Fatal level
adb logcat *:S //silent,higest priority, on which nothing is ever printed
```

```C++
adb logcat -v brief //Display priority/tag and PID of the process issuing the message (default format).
adb logcat -v process //Display PID only.)
adb logcat -v tag //Display the priority/tag only.
adb logcat -v raw //Display the raw log message, with no other metadata fields.
adb logcat -v time //Display the date, invocation time, priority/tag, and PID of the process issuing the message.
adb logcat -v threadtime //Display the date, invocation time, priority, tag, and the PID and TID of the thread issuing the message.
adb logcat -v long //Display all metadata fields and separate messages with blank lines.
```

