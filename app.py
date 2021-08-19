f = open("/dev/char_device", "w")  # open
f.write("helloworld")              # write
f.close()                          # release
f = open("/dev/char_device", "r")  # open
string = f.read()                  # read / f.read() with no parameters means reading the whole file
f.close()                          # release
print(string)                      # helloworld 

f = open("/dev/char_device", "w")  # open
f.write("testing")                 # write
f.close()                          # release
f = open("/dev/char_device", "r")  # open
string = f.read()                  # read
f.close()                          # release
print(string)                      # helloworldtesting

f = open("/dev/char_device", "w")  # open
f.write("driver")                  # write
f.close()                          # release
f = open("/dev/char_device", "r")  # open
string = f.read()                  # read
f.close()                          # release
print(string)                      # verloworldtestingdri

f = open("/dev/char_device", "w")  # open
f.write("ABCD")                    # write
f.close()                          # release
f = open("/dev/char_device", "r")  # open
string = f.read()                  # read
f.close()                          # release
print(string)                      # verABCDrldtestingdri
