## Android Handler & Message

<center>
  @<img src = "917743-20160520195457373-1290367512.jpg"/>
</center>



- UI thread

  Main thread. When create the UI thread, system will init Looper object adn create related MessageQueue

- Handler

  Send Message and handle message. If wish Handler work normal, current thread need Looper.

- Message

- MessageQueue

- Looper

  Continously push message from message queue and dispatch them

