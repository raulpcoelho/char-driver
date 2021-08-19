f = open("/dev/mychardev", "w")         # open
f.write("helloworld")                   # write
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

f = open("/dev/mychardev", "w")         # open
f.write("ABCD")                         # write
f.close()                               # release
f = open("/dev/mychardev", "r")         # open
string = f.read()                       # read
f.close()                               # release
print(string)                           # verABCDrldtestingdri

