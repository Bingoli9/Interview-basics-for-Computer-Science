## Blob Url

Blob URLs or Object-URLs are used with a Blob or File Object

Blob URLs can only be generated internally by the browser.

URL.createObjectURL() will create a special reference to the Blob or File object which later can be released using URL.revokeObjectURL(). These URLs can only be used locally in the single instance of the browser and in the same session





#### What is blob url

Blob URL/Object URL is a pseudo protocol to allow Blob and File objects to be used as URL source for things like images, download links for binary data and so forth.

For example, you can not hand an image object raw byte-data as it would not know what to do with it. It requires for example images(which are binary data) to be loaded via URLs. This applies to anything that require an URL as source. 

Instead of uploading the binary data, then serve it back via an URL it is better to use an extra local step to be able to access the data directly without going via a server.

You need to encapsulate the binary data as a BLOB object, then use `URL.createObjectURL()` to generate a local URL for it:

```C++
var blob = new Blob([arrayBufferWithPNG], {type: "image/png"}),
    url = URL.createObjectURL(blob),
    img = new Image();

img.onload = function() {
    URL.revokeObjectURL(this.src);     // clean-up memory
    document.body.appendChild(this);   // add image to DOM
}

img.src = url;                         // can now "stream" the bytes
```

