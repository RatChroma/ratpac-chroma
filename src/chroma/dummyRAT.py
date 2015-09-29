# Creates fake step data and sends to ZINC

import zmq
import numpy as np
import ratchromadata_pb2
import photonHit_pb2

def get_step_data():
    steps = np.load( 'steps.npy' )
    ratdata = ratchromadata_pb2.ChromaData()
    for x in steps:
        step = ratdata.stepdata.add()
        step.step_start_x = x[0]
        step.step_start_y = x[1]
        step.step_start_z = x[2]
        step.step_end_x   = x[3]
        step.step_end_y   = x[4]
        step.step_end_z   = x[5]
        step.step_start_t = x[6]
        step.step_end_t   = x[6]
        step.material     = "LAr"
        step.nphotons     = np.random.poisson( 10.0 )
    return ratdata

if __name__=="__main__":
    context = zmq.Context().instance()
    rat_client = context.socket(zmq.REQ)
    rat_client.connect("tcp://localhost:5554")
    
    # connect
    rat_client.send( "RDY" )
    rat_client.recv()
    print "READY"

    # send config
    rat_client.send_multipart( ["CFG","blah-blah"] )
    reply = rat_client.recv_multipart()
    print "SENT CONFIG: ",reply

    # send data
    nevents = 10
    for evt in xrange(0,nevents):
        data = get_step_data()
        msg = data.SerializeToString()
        rat_client.send_multipart( ["EVT",msg] )
        print "SENT STEP REQ (",evt+1,")"
        msg_chromahits = rat_client.recv_multipart()
        print "RECV PHOTON HITS"
        chromahits = photonHit_pb2.PhotonHits()
        chromahits.ParseFromString( msg_chromahits[-1] )
        print chromahits
        print "End of event ",evt+1
