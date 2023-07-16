# Simulator Instance Creation
set ns [new Simulator]

# Fixing the coordinate of simulation area
set val(x) 500
set val(y) 500

# Define options
set val(chan) "Channel/WirelessChannel" ;# channel type
set val(prop) "Propagation/TwoRayGround" ;# radio-propagation model
set val(netif) "Phy/WirelessPhy" ;# network interface type
set val(mac) "Mac/802_11" ;# MAC type
set val(ifq) "Queue/DropTail/PriQueue" ;# interface queue type
set val(ll) "LL" ;# link layer type
set val(ant) "Antenna/OmniAntenna" ;# antenna model
set val(ifqlen) 50 ;# max packet in ifq
set val(nn) 3 ;# number of mobilenodes
set val(rp) "AODV" ;# routing protocol
set val(x) 500 ;# X dimension of topography
set val(y) 400 ;# Y dimension of topography
set val(stop) 10.0 ;# time of simulation end

# Set up topography object
set topo [new Topography]
$topo load_flatgrid $val(x) $val(y)

# Nam File Creation (network animator)
set namfile [open sample1.nam w]

# Tracing all the events and configuration
$ns namtrace-all-wireless $namfile $val(x) $val(y)

# Trace File creation
set tracefile [open sample1.tr w]

# Tracing all the events and configuration
$ns trace-all $tracefile

# General operational descriptor - storing the hop details in the network
create-god $val(nn)

# Configure the nodes
$ns node-config -adhocRouting $val(rp) \
-llType $val(ll) \
-macType $val(mac) \
-ifqType $val(ifq) \
-ifqLen $val(ifqlen) \
-antType $val(ant) \
-propType $val(prop) \
-phyType $val(netif) \
-channelType $val(chan) \
-topoInstance $topo \
-agentTrace ON \
-routerTrace ON \
-macTrace OFF \
-movementTrace ON

# Node Creation
set node1 [$ns node]
# Initial color of the node
$node1 color black

# Location fixing for node1
$node1 set X_ 200
$node1 set Y_ 100
$node1 set Z_ 0

set node2 [$ns node]
$node2 color black

# Location fixing for node2
$node2 set X_ 200
$node2 set Y_ 300
$node2 set Z_ 0

set node3 [$ns node]
$node3 color black

# Location fixing for node3
$node3 set X_ 400
$node3 set Y_ 200
$node3 set Z_ 0

# Label and coloring
$ns at 0.1 "$node1 color blue"
$ns at 0.1 "$node1 label Node1"
$ns at 0.1 "$node2 label Node2"
$ns at 0.1 "$node3 label Node3"

# Size of the nodes
$ns initial_node_pos $node1 30
$ns initial_node_pos $node2 30
$ns initial_node_pos $node3 30

# Ending nam and the simulation
$ns at $val(stop) "$ns nam-end-wireless $val(stop)"
$ns at $val(stop) "stop"

# Stopping the scheduler
$ns at 10.01 "puts \"end simulation\" ; $ns halt"

proc stop {} {
    global namfile tracefile ns
    $ns flush-trace
    close $namfile
    close $tracefile
    # Executing nam file
    exec nam sample1.nam &
}

# Create TCP agents for each TCP variation
set tcpTahoe12 [new Agent/TCP]
set tcpTahoe23 [new Agent/TCP]

# Attach TCP agents to the corresponding nodes
$ns attach-agent $node1 $tcpTahoe12
$ns attach-agent $node2 $tcpTahoe23

# Create sink agents for receiving
set sink2 [new Agent/TCPSink]
set sink3 [new Agent/TCPSink]
$ns attach-agent $node2 $sink2
$ns attach-agent $node3 $sink3

# Connect TCP agents with the sink agents
$ns connect $tcpTahoe12 $sink2
$ns connect $tcpTahoe23 $sink3

# Attach TCP agents to the FTP applications
set ftpTahoe12 [new Application/FTP]
set ftpTahoe23 [new Application/FTP]
$ftpTahoe12 attach-agent $tcpTahoe12
$ftpTahoe23 attach-agent $tcpTahoe23

# Data packet generation starting time
$ns at 1.0 "$ftpTahoe12 start"
$ns at 3.0 "$ftpTahoe23 start"

# Data packet generation ending time
$ns at 6.0 "$ftpTahoe12 stop"
$ns at 8.0 "$ftpTahoe23 stop"

# Start the simulation
$ns run
