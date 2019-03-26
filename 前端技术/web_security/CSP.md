## CSP

内容安全策略(CSP, Content Security Policy) 是一个附加的安全层，用于帮助检测和缓解某些类型的攻击，包括跨站脚本（XSS）和数据注入等攻击。这些攻击可用于实现从数据窃取到网站破坏或作为恶意软件分发版本等用途。

### XSS

Cross-site scripting(XSS) is a type of computer security vulnerablity typically found in web application. XSS enables attackers to inject client-side scripts into web pages viewed by other users. A cross-site scripting vulnerablity may be used by attackers to bypass access controls such as the same-origin policy.  

#### XSS types

- Non-persistent (reflected)

  The non-persistent cross-site scripting vulnerability is by far the most basic type of web vulnerability. These holes show up when the data provided by a web client, most commonly in HTTP query parameters, is used immediately by server-side scripts to parse and display a page of results for and to that user, without properly sanitizing the request

- Persistent (or stored)

  The persistent XSS vulnerability is a more devastaing vatiant of a cross-site scripting flaw: it occurs when the data provided by the attacker is saved by the server, and then permanently displayed on "normal" pages returned to other users in the course of regulat browsing, without proper HTML escaping. 

- Server-side versus DOM-based vulnerabilities

  As the JvaScript code was also processing user input and rendering it in the web page content, a new sub-class of reflected XSS attacks started to appear that was called DOM-based XSS. n a DOM-based XSS attack, the malicious data does not touch the web server. Rather, it is being reflected by the JavaScript code, fully on the client side

- self-xss

- mutated xss

