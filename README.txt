= USE (x86) for run the project
= For run the project,first of all build all three solution.

= KEYEVENT:: MOVEMENT TO THE BALL
W = Move in forward direction 
S = Move in Backword direction
A = Move in Leftside
D = Move in Rightside 

= For the CAMARA CONTROL use arrow key for zoom in, zoom out and change the direction of camara.

= For DEBUG RENDERING : '9' => for active the debug rendering.
			'0' => for deactive debug rendering.

= All the model load with external text file which is inside the FirstOpenGl folder("Scene.txt").

///////////////////////////////////////////////////////////////////////////////////////////////////////
There is three type of the opponents for this project 
1. Angry = which is in 
2. Curious = which is in 
3. Followers = which is in 

THA STATES ENGAGE while the we are close enough to the enemies. (Radius 20)
Red small balls are angry, they turn red while chasing us, they turn white while running away
A bit bigger blue balls are curious and they rutn yellow while running away

Little blue quidich ball looking sphere is the follower that follows your trail that you leave behind, the interval at which the trail position is recorded can be changes in physics.cpp file in the physics step method with a time variable

The Violet/Purple  portals circle you through them
The third blue portal at the corner is the one that resets the state and spawns you back to the origin