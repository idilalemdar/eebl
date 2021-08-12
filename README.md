# Electronic Emergency Brake Light Warning Application

This is a simulation application where two cars are connected with each other through V2V connection. The car which is on the front is responsible for warning the other one in case of an emergency brake.

To run the application:
    make follower
    ./follower initial_speed initial_position server_ip

Then in another device:
    make lead
    ./lead fname initial_speed initial_position server_ip

    where fname is the name of the file where brake positions are kept.

Valid inputs:
    initial speed = 0-90 km/h
    initial_position = As indicated in the task pdf, however lead car must  be ahead of the follower car.
    server_ip: IP of the device where follower car's code is running.
