# ArduinoSimpleLogging

Simple logging-framework for Arduino supporting levels and handlers.

It provides a static `Logger` instance that has static `Print` instances as members.
These members are `debug`, `info`, `warning` and `error` and represent preconfigured log targets for the available log levels.

As these are `Print` instances, you can use them as drop-in-replacement for `Serial`.
For example instead of `Serial.println("Hello")` you just write `Logger.debug.println("Hello")`.
This will print the String `Hello` to all streams that are configured for `DEBUG`.

To configure a `Print` instance for a log level you simply add it as log handler.
For example, to log all log messages to `Serial` you need to call:
```cpp
Logger.addHandler(Logger.DEBUG, Serial);
```

Log levels are including.
That means, that when you configure a handler for a certain level, you'll get everything up to this level.
The available levels are: `ERROR`, `WARNING`, `INFO`, `DEBUG` with debug the highest level.
So if you configure your Handler for `DEBUG`, you'll get messages for all levels.
If you configure for `ERROR`, you'll get only error messages.
