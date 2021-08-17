f = open("/dev/mychardev", "w")
f.write("hello")
f.close()
f = open("/dev/mychardev", "r")
string = f.read()
print(string)
f.close()


f = open("/dev/mychardev", "w")
f.write("hello")
f.close()
f = open("/dev/mychardev", "r")
string = f.read()
print(string)


f = open("/dev/mychardev", "w")
f.write("hello")
f.close()
f = open("/dev/mychardev", "r")
string = f.read()
print(string)

