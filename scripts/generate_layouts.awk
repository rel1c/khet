#!/usr/bin/awk -f

BEGIN {
    f = "initBitboard"
    v = "std::vector<Square>"
    FS = "[=,]"
    section = 0
    delete red[0]
    delete silver[0]
    delete anubis[0]
    delete pharaoh[0]
    delete pyramid[0]
    delete scarab[0]
    delete sphinx[0]
    delete north[0]
    delete east[0]
    delete south[0]
    delete west[0]
}

function push(array, item) {
    array[length(array)+1] = item
}

# layout title
/^\[[A-Za-z]*\]/ {
    if (!section) {
        section = 1
    }
}

/^[A-J][1-8]=[A-Za-z,]*$/ {
    if ($2 == "Silver") {
        push(silver, $1)
    } else if ($2 == "Red") {
        push(red, $1)
    }
    if ($3 == "Anubis") {
        push(anubis, $1)
    } else if ($3 == "Pharaoh") {
        push(pharaoh, $1)
    } else if ($3 == "Pyramid") {
        push(pyramid, $1)
    } else if ($3 == "Scarab") {
        push(scarab, $1)
    } else if ($3 == "Sphinx") {
        push(sphinx, $1)
    }
    if ($4 == "North") {
        push(north, $1)
    } else if ($4 == "East") {
        push(east, $1)
    } else if ($4 == "South") {
        push(south, $1)
    } else if ($4 == "West") {
        push(west, $1)
    }
}

END {
    i = 1
    out = ""
    while (i <= length(red)) {
        if (i == 1) {
            out = red[i++]
        } else {
            out = out ", " red[i++]
        }
    }
    print "red_ = initBitboard(std::vector<Square> {" 
    print "\t" out
    print "});"

    i = 1
    out = ""
    while (i <= length(silver)) {
        if (i == 1) {
            out = silver[i++]
        } else {
            out = out ", " silver[i++]
        }
    }
    print "silver_ = initBitboard(std::vector<Square> {" 
    print "\t" out
    print "});"

    i = 1
    out = ""
    while (i <= length(north)) {
        if (i == 1) {
            out = north[i++]
        } else {
            out = out ", " north[i++]
        }
    }
    print "north_ = initBitboard(std::vector<Square> {" 
    print "\t" out
    print "});"

    i = 1
    out = ""
    while (i <= length(east)) {
        if (i == 1) {
            out = east[i++]
        } else {
            out = out ", " east[i++]
        }
    }
    print "east_ = initBitboard(std::vector<Square> {" 
    print "\t" out
    print "});"

    i = 1
    out = ""
    while (i <= length(south)) {
        if (i == 1) {
            out = south[i++]
        } else {
            out = out ", " south[i++]
        }
    }
    print "south_ = initBitboard(std::vector<Square> {" 
    print "\t" out
    print "});"

    i = 1
    out = ""
    while (i <= length(west)) {
        if (i == 1) {
            out = west[i++]
        } else {
            out = out ", " west[i++]
        }
    }
    print "west_ = initBitboard(std::vector<Square> {" 
    print "\t" out
    print "});"

    i = 1
    out = ""
    while (i <= length(anubis)) {
        if (i == 1) {
            out = anubis[i++]
        } else {
            out = out ", " anubis[i++]
        }
    }
    print "anubis_ = initBitboard(std::vector<Square> {" 
    print "\t" out
    print "});"

    i = 1
    out = ""
    while (i <= length(pharaoh)) {
        if (i == 1) {
            out = pharaoh[i++]
        } else {
            out = out ", " pharaoh[i++]
        }
    }
    print "pharaoh_ = initBitboard(std::vector<Square> {" 
    print "\t" out
    print "});"

    i = 1
    out = ""
    while (i <= length(pyramid)) {
        if (i == 1) {
            out = pyramid[i++]
        } else {
            out = out ", " pyramid[i++]
        }
    }
    print "pyramid_ = initBitboard(std::vector<Square> {" 
    print "\t" out
    print "});"

    i = 1
    out = ""
    while (i <= length(scarab)) {
        if (i == 1) {
            out = scarab[i++]
        } else {
            out = out ", " scarab[i++]
        }
    }
    print "scarab_ = initBitboard(std::vector<Square> {" 
    print "\t" out
    print "});"
}
