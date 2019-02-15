# CPP-ConsoleMessenger

## Server

Server request handling is based on a chain of responsibilities.

To add new request to handle add class inherited from RequestResolverAbstract class and add object to list in constructor of Resolver class.

### Dependencies
```
Boost::asio
C++11
```

### Building
```
mkdir build
cd build
cmake ..
make
```

### Using
```
./Server
```

## Client
Work in progress...
