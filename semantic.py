# Rappel des types struct.pack usuelles :
# B  unsigned char
# H  unsigned short
# I  unsigned int
# b  signed char
# h  signed short
# i  signed int
# f  float

# yymmjjhhmm
version = 1404111942

class Common(Proto):
    def __init__(self):
        print("Common")
        super(Common, self)

    unimplemented = Packet(251, "pic")
    test = Packet(252, "both", [
            ("B", "B"),
            ("H", "H"),
            ("I", "I"),
            ("b", "b"),
            ("h", "h"),
            ("i", "i"),
            ("f", "f")
        ])
    error = Packet(253, "pic")
    getId = Packet(254, "arm")
    id = Packet(255, "pic", [
            ("id", "B")
        ])

class Asserv(Proto):
    type = 2

    stop = Packet(1, "arm")
    ausecours = Packet(1, "arm")
    block = Packet(2, "arm")
    done = Packet(3, "pic")


    motion_pos = Packet(10, "arm", [
        ("x", "f"),
        ("y", "f")
        ])
    motion_speed = Packet(11, "arm", [
        ("v", "f"),
        ("vTheta", "f")
        ])
    motion_angle = Packet(12, "arm", [
        ("theta", "f")
        ])


    getPos = Packet(30, "arm")
    pos = Packet(31, "pic", [
        ("x", "f"),
        ("y", "f"),
        ("theta", "f")
        ])
    getSpeed = Packet(40, "arm")
    speed = Packet(41, "pic", [
        ("v", "f"),
        ("vTheta", "f")
        ])

    init_arm = Packet(50, "arm", [
        ("choix", "H")
        ])
    catch_arm = Packet(51, "arm", [
        ("choix", "H")
        ])
    stock_arm = Packet(52, "arm", [
        ("choix", "H")
        ])
    pull_arm = Packet(53, "arm", [
        ("choix", "H")
        ])
    push_arm = Packet(54, "arm", [
        ("choix", "H")
        ])
    launch_net = Packet(55, "arm")


#    odoBroadcastOn = Packet(43, "arm")
#    odoBroadcastOff = Packet(44, "arm")
#    odoBroadcastToggle = Packet(45, "arm")
#    odoDelay = Packet(46, "arm", [("delay", "I")])


# Rappel des types struct.pack usuelles :
# B  unsigned char
# H  unsigned short
# I  unsigned int
# b  signed char
# h  signed short
# i  signed int
# f  float
