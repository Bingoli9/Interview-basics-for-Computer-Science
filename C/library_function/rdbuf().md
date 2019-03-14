## rdbuf()

rdbuf can be used to implement that content pointed by one stream object output by another stream object. For example:

For one file content, if you want to output the content of a file to the display, we can:

```C++
ifstream infile("test.txt");
cout << infile.rdbuf();
```

