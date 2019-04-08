## Package Manager

#### adb shell pm list packages

Prints all packages, optionally only those whose package name contains the text in \<FILTER>

#### adb shell pm path 

Print the path to the APK of the given \<PACKAGE>

```C++
adb shell pm path com.android.phone
```

#### adb shell pm clear

Deletes all data associated with a package.

```C++
adb shell pm clear com.test.abc
```

