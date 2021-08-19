f = open("/dev/mychardev", "w")         # open
f.write("hello")                        # write
f.close()                               # release
f = open("/dev/mychardev", "r")         # open
string = f.read()                       # read
f.close()                               # release
print(string)                           # hello

f = open("/dev/mychardev", "w")         # open
f.write("world")                        # write
f.close()                               # release
f = open("/dev/mychardev", "r")         # open
string = f.read()                       # read
f.close()                               # release
print(string)                           # helloworld

f = open("/dev/mychardev", "w")         # open
f.write("testing")                      # write
f.close()                               # release
f = open("/dev/mychardev", "r")         # open
string = f.read()                       # read  
f.close()                               # release
print(string)                           # helloworldtesting

f = open("/dev/mychardev", "w")         # open
f.write("driver")                       # write
f.close()                               # release
f = open("/dev/mychardev", "r")         # open
string = f.read()                       # read
f.close()                               # release
print(string)                           # verloworldtestingdri
