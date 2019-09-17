#include"myPhysics.h"



void myPhysics::ReadFileToToken(std::ifstream &file, std::string token)
{
	bool bKeepReading = true;
	std::string garbage;
	do
	{
		file >> garbage;		// Title_End??
		if (garbage == token)
		{
			return;
		}
	} while (bKeepReading);
	return;
}

float health = 20;

std::vector<myPhysics::object1> myPhysics::InitializePhysics(std::string file)
{

	std::vector <object1> myvec;
	object1 myobj;
	std::ifstream plyFile(file.c_str());

	if (!plyFile.is_open())
	{	// Didn't open file, so return

	}


	ReadFileToToken(plyFile, "models");
	int count;
	plyFile >> count;
	for (int i = 1; i <= count; i++)
	{

		ReadFileToToken(plyFile, std::to_string(i));
		ReadFileToToken(plyFile, "position");
		plyFile >> myobj.pos.x;
		plyFile >> myobj.pos.y;
		plyFile >> myobj.pos.z;

		ReadFileToToken(plyFile, "orientation");
		plyFile >> myobj.ori.x;
		plyFile >> myobj.ori.y;
		plyFile >> myobj.ori.z;


		ReadFileToToken(plyFile, "orientation2");
		plyFile >> myobj.or2.x;
		plyFile >> myobj.or2.y;
		plyFile >> myobj.or2.z;

		ReadFileToToken(plyFile, "scale");
		plyFile >> myobj.scale;

		ReadFileToToken(plyFile, "color");
		plyFile >> myobj.color.a;
		plyFile >> myobj.color.r;
		plyFile >> myobj.color.g;
		plyFile >> myobj.color.b;

		ReadFileToToken(plyFile, "name");
		plyFile >> myobj.name;

		ReadFileToToken(plyFile, "type");
		plyFile >> myobj.typer;
		if (myobj.typer == "sphere")
		{
			myobj.type = eTypeOfObject::SPHERE;
		}
		else
		{
			myobj.type = eTypeOfObject::PLANE;
		}

		ReadFileToToken(plyFile, "physics");
		plyFile >> myobj.phys;

		myvec.push_back(myobj);

	}
	return myvec;
}





void myPhysics::PhysicsStep(double deltaTime, force &wforce, force &sforce, force &leftforce, force &rightforce, force &upforce, std::vector<glm::vec3> &disp, std::vector<glm::vec3> &rot, std::vector<object1> &my, std::vector<int> &collision)
{
	//std::cout << glfwGetTime() <<std::endl;
	std::cout << "HEALTH: ";
	for (int i = 0; i < health; i++)
	{
		std::cout << "//";
	}
	std::cout << std::endl;
	
	
	if (collision.size() != my.size())
	{
		for (int i = 0; i < my.size(); i++)
		{
			collision.push_back(0);
		}
	}
	
	const glm::vec3 GRAVITY = glm::vec3(0.0f, -5.0f, 0.0f);
	for (int index = 0; index < my.size(); index++)
	{
		
		// Is this object to be updated?
		object1 pCurGo = my[index];
		if (!pCurGo.phys)
		{
			continue;
		}

		glm::vec3 a;
		a = (GRAVITY);
		glm::vec3 deltaVelocity = ((a*(float)deltaTime / 4.0f) + ((a*(float)deltaTime / 2.0f)) + (3.0f*(a*(float)deltaTime / 2.0f)) + (a*(float)deltaTime)) / 4.0f;
		glm::vec3 deltaVelocity2 = ((float)deltaTime * a);
		switch (pCurGo.type)
		{
		case eTypeOfObject::SPHERE:

			const float SURFACEOFGROUND = -1.5f;
			const float LEFTSIDEWALL = 14.5f*my[0].scale;
			const float RIGHTSIDEWALL = -13.5f*my[0].scale;

			const float BACKWALL = -13.5f*my[0].scale;
			const float FRONTWALL = 14.5f*my[0].scale;


			
			// 
			//my[1].color = glm::vec4(0, 1, 0, 1);
			if (index == 1)
			{



				if (glfwGetTime() - time >= 0.5)
				{
					time = glfwGetTime();
					path.push_back(my[1].pos);
					std::cout << "(" << my[1].pos.x << "," << my[1].pos.z << std::endl;
					//pathaccess++;
				}
				if (wforce.on == 1)
				{
					a = (wforce.direction * wforce.strength * glm::vec3(1, 0, 1)) * 15.0f;
					deltaVelocity = ((a*(float)deltaTime / 4.0f) + ((a*(float)deltaTime / 2.0f)) + (3.0f*(a*(float)deltaTime / 4.0f)) + (a*(float)deltaTime)) / 6.0f;

					pCurGo.vel += deltaVelocity;
					

				}
				else
				{
					if (abs(pCurGo.vel.x) > 0 || abs(pCurGo.vel.z) >0)
						pCurGo.vel -= pCurGo.vel  * glm::vec3(1, 0, 1) / 20.0f;
				}

				if (sforce.on == 1)
				{
					a = (-wforce.direction * wforce.strength * glm::vec3(1, 0, 1)) * 15.0f;
					deltaVelocity = ((a*(float)deltaTime / 4.0f) + ((a*(float)deltaTime / 2.0f)) + (3.0f*(a*(float)deltaTime / 4.0f)) + (a*(float)deltaTime)) / 6.0f;

					pCurGo.vel += deltaVelocity;

				}
				else
				{
					if (abs(pCurGo.vel.x) > 0 || abs(pCurGo.vel.z) >0)
						pCurGo.vel -= pCurGo.vel  * glm::vec3(1, 0, 1) / 20.0f;
				}

				if (leftforce.on == 1 )
				{
					a = (leftforce.direction * leftforce.strength * glm::vec3(1, 0, 1)) * 15.0f;
					deltaVelocity = ((a*(float)deltaTime / 4.0f) + ((a*(float)deltaTime / 2.0f)) + (3.0f*(a*(float)deltaTime / 4.0f)) + (a*(float)deltaTime)) / 4.0f;

					pCurGo.vel += deltaVelocity;

				}

				else
				{
					if (abs(pCurGo.vel.x) > 0 || abs(pCurGo.vel.z) >0)
						pCurGo.vel -= pCurGo.vel  * glm::vec3(1, 0, 1) / 20.0f;
				}

				if (rightforce.on == 1)
				{
					a = (rightforce.direction * rightforce.strength * glm::vec3(1, 0, 1)) * 15.0f;
					deltaVelocity = ((a*(float)deltaTime / 4.0f) + ((a*(float)deltaTime / 2.0f)) + (3.0f*(a*(float)deltaTime / 4.0f)) + (a*(float)deltaTime)) / 4.0f;

					pCurGo.vel += deltaVelocity;

				}
				else
				{
					if (abs(pCurGo.vel.x) > 0 || abs(pCurGo.vel.z) >0)
						pCurGo.vel -= pCurGo.vel  * glm::vec3(1, 0, 1) / 20.0f;
				}

				if (upforce.on == 1 && collision[index] != 1)
				{
					deltaVelocity += upforce.direction * upforce.strength;
					pCurGo.vel += deltaVelocity;
				}
				else
				{
					if ((pCurGo.vel.y) > 0)
						pCurGo.vel.y -= pCurGo.vel.y / 2.0f;
				}

				if (collision[index] == 1)
				{
					my[index].vel = 5.0f*my[index].vel*glm::vec3(1, 0, 1);
				}


			}
		
			/*for (int j = 0; j < my.size(); j++)
			{
				if (my[j].type == eTypeOfObject::SPHERE && index != j)
				{


					if (glm::distance(my[index].pos, my[j].pos) <= my[index].scale + my[j].scale)
					{

						pCurGo.vel -= 10.0f*(my[index].pos - my[index].pos)*(float)deltaTime;
						
					}
					else
					{
						
						
					}
				}
			}*/
			
			float control=0.6;
			glm::vec3 diffvec;
			glm::vec3 correctdir;
			glm::vec3 velvec;
			glm::vec3 diffvecabs;
			glm::vec3 posvec;



			
			if (pCurGo.scale == 0.5f )
			{
				
				//To prevent them going into each other, Simple Collision Detection:
				for (int j = 0; j < my.size(); j++)
				{
					if (index != j && index != 1 && j != 1 && j!=7)
					{
						if (glm::distance(my[j].pos, my[index].pos) <= 1.0f)
						{
							my[j].vel += glm::normalize((my[j].pos - my[index].pos));
						}

					}
				}
				velvec = glm::normalize (pCurGo.vel);

				correctdir =  glm::normalize(my[1].pos - pCurGo.pos);
				diffvec = abs( ( correctdir - velvec  )    );
				//std::cout << "(" << diffvec.x << "," << diffvec.z << ")" << std::endl;
				diffvecabs = abs(diffvec);
				posvec = glm::normalize(my[1].pos - pCurGo.pos);

				/////////////////////////////////////////////////////////////////////////////////
				//PERSUE
				if (glm::distance(pCurGo.pos, my[1].pos) <= 20.0f &&health>0)
				{
					if (abs((glm::normalize(wforce.direction) + posvec).x) >= 0.4f || abs((glm::normalize(wforce.direction) + posvec).z) >= 0.4f)
					{

						my[index].color = glm::vec4(1.0, 0.0, 0.0, 1.0);

						if (glm::distance(my[1].pos, pCurGo.pos) >= 2.0f)
						{

							pCurGo.vel += 6.0f*glm::normalize(my[1].pos - pCurGo.pos)*(float)deltaTime;
						}
						else
						{
							my[1].color = glm::vec4(1, 1, 0, 1);
							health -= 0.01;
							if (abs(pCurGo.vel.x) > 0 || abs(pCurGo.vel.z) > 0)
							{
								pCurGo.vel -= pCurGo.vel / 5.0f;
							}

						}
						if (diffvecabs.x >= control || diffvecabs.z >= control)
						{
							pCurGo.vel -= pCurGo.vel / 100.0f * glm::vec3(1, 0, 1);
						}

					}
					else
					{
						my[1].color = glm::vec4(0, 1, 0, 1);
						my[index].color = glm::vec4(1.0, 1.0, 1.0, 1.0);
						pCurGo.vel -= 6.0f*glm::normalize(my[1].pos - pCurGo.pos)*(float)deltaTime;
					}
				}
				
				if (health <= 0)
				{
					if (abs((glm::normalize(wforce.direction) + posvec).x) >= 0.4f || abs((glm::normalize(wforce.direction) + posvec).z) >= 0.4f)
					{

						my[index].color = glm::vec4(1.0, 0.0, 0.0, 1.0);

						if (glm::distance(my[1].pos, pCurGo.pos) >= 2.0f)
						{

							pCurGo.vel += 6.0f*glm::normalize(my[1].pos - pCurGo.pos)*(float)deltaTime;
						}
						else
						{
							my[1].color = glm::vec4(1, 1, 0, 1);
							health -= 0.01;
							if (abs(pCurGo.vel.x) > 0 || abs(pCurGo.vel.z) > 0)
							{
								pCurGo.vel -= pCurGo.vel / 5.0f;
							}

						}
						if (diffvecabs.x >= control || diffvecabs.z >= control)
						{
							pCurGo.vel -= pCurGo.vel / 100.0f * glm::vec3(1, 0, 1);
						}

					}
					else
					{
						my[1].color = glm::vec4(0, 1, 0, 1);
						my[index].color = glm::vec4(1.0, 1.0, 1.0, 1.0);
						pCurGo.vel -= 6.0f*glm::normalize(my[1].pos - pCurGo.pos)*(float)deltaTime;
					}
				}
				/////////////////////////////////////////////////////////////////////////////////
				



				//////////////////////////////////////////////////////////
				//ROTATION
				/////////////////////////////////////////////////////////
				if (diffvecabs.x >= 0.1)
				{
					my[index].or2.y += diffvec.x*(float)deltaTime;
				}
				//////////////////////////////////////////////////////////
				/////////////////////////////////////////////////////////
					
				//rot[index]= glm::vec3(0,5.0f, 0);
				//pCurGo.or2 = glm::vec3(0,5.0f, 0);

			
			}
			
			if (pCurGo.scale == 0.45f)
			{
			
				
				if (path.size() >= 1)
				{
					glm::vec3 posdiff = abs(path[pathaccess] - pCurGo.pos);
					glm::vec3 gotodirection = glm::normalize(path[pathaccess] - pCurGo.pos);
					if (glm::distance(path[pathaccess],pCurGo.pos) >= 0.3f)
					{
						//std::cout << "following position" <<pathaccess<<":  "<< path[pathaccess].x << "," << path[pathaccess].z << std::endl;
						pCurGo.vel = 2000.0f*gotodirection *	(float)deltaTime;
					}
					else
					{
						
						if (pathaccess < path.size() - 1)
						{
							pCurGo.vel -= pCurGo.vel;
							pathaccess++;
						}
						/*if (abs(pCurGo.vel.x) >= 0.01 || abs(pCurGo.vel.z) >= 0.01)
						{
							pCurGo.vel -= pCurGo.vel;
							
						}
						else
						{
							if (pathaccess < path.size() - 1)
							{
								pathaccess++;
							}
						}*/
					}
				}
			}

			if (pCurGo.scale == 0.75f)
			{

				//To prevent them going into each other, Simple Collision Detection:
				for (int j = 0; j < my.size(); j++)
				{
					if (index != j && index != 1 && j != 1 && j != 7)
					{
						if (glm::distance(my[j].pos, my[index].pos) <= 1.0f)
						{
							my[j].vel += glm::normalize((my[j].pos - my[index].pos));
						}

					}
				}
				velvec = glm::normalize(pCurGo.vel);

				correctdir = glm::normalize(my[1].pos - pCurGo.pos);
				diffvec = abs((correctdir - velvec));
				//std::cout << "(" << diffvec.x << "," << diffvec.z << ")" << std::endl;
				diffvecabs = abs(diffvec);
				posvec = glm::normalize(my[1].pos - pCurGo.pos);

				/////////////////////////////////////////////////////////////////////////////////
				//PERSUE
				if (glm::distance(pCurGo.pos, my[1].pos) <= 20.0f)
				{
					if (abs((glm::normalize(wforce.direction) + posvec).x) >= 0.4f || abs((glm::normalize(wforce.direction) + posvec).z) >= 0.4f)
					{

						my[index].color = glm::vec4(0.0, 0.0, 1.0, 1.0);

						if (glm::distance(my[1].pos, pCurGo.pos) >= 2.0f)
						{

							pCurGo.vel += 1.0f*glm::normalize(my[1].pos - pCurGo.pos)*(float)deltaTime;
						}
						else
						{
							if (abs(pCurGo.vel.x) > 0 || abs(pCurGo.vel.z) > 0)
							{
								pCurGo.vel -= pCurGo.vel / 5.0f;
							}

						}
						if (diffvecabs.x >= control || diffvecabs.z >= control)
						{
							pCurGo.vel -= pCurGo.vel / 100.0f * glm::vec3(1, 0, 1);
						}

					}
					else
					{
						my[index].color = glm::vec4(1.0, 1.0, 0.0, 1.0);
						pCurGo.vel -= 6.0f*glm::normalize(my[1].pos - pCurGo.pos)*(float)deltaTime;
					}
				}
				/*else
				{
					pCurGo.vel -= pCurGo.vel / 2.0f;
				}*/
				
				/////////////////////////////////////////////////////////////////////////////////




				//////////////////////////////////////////////////////////
				//ROTATION
				/////////////////////////////////////////////////////////
				if (diffvecabs.x >= 0.1)
				{
					my[index].or2.y += diffvec.x*(float)deltaTime;
				}
				//////////////////////////////////////////////////////////
				/////////////////////////////////////////////////////////

				//rot[index]= glm::vec3(0,5.0f, 0);
				//pCurGo.or2 = glm::vec3(0,5.0f, 0);


			}
			if ((pCurGo.pos.y - pCurGo.scale / 2.0f) <= SURFACEOFGROUND && upforce.on == 0)
			{
				pCurGo.vel.y = 0;
				deltaVelocity.y = 0;
			}

			if ((pCurGo.pos.x - pCurGo.scale / 2.0f) <= RIGHTSIDEWALL && (float)deltaTime*pCurGo.vel.x<0)
			{
				pCurGo.vel.x = 0;
				deltaVelocity.x = 0;
			}

			if ((pCurGo.pos.x - pCurGo.scale / 2.0f) >= LEFTSIDEWALL && (float)deltaTime*pCurGo.vel.x>0)
			{
				pCurGo.vel.x = 0;
				deltaVelocity.x = 0;

			}

			if ((pCurGo.pos.z - pCurGo.scale / 2.0f) <= BACKWALL && (float)deltaTime*pCurGo.vel.z<0)
			{
				pCurGo.vel.z = 0;
				deltaVelocity.z = 0;
			}

			if ((pCurGo.pos.z - pCurGo.scale / 2.0f) >= FRONTWALL && (float)deltaTime*pCurGo.vel.z>0)
			{
				pCurGo.vel.z = 0;
				deltaVelocity.z = 0;
			}

			
			pCurGo.vel = pCurGo.vel + deltaVelocity;

			glm::vec3 deltaPosition = (float)deltaTime * pCurGo.vel;	

			disp[index] = (deltaPosition);
			if (pCurGo.pos.x <= BACKWALL +5 && pCurGo.pos.z <= RIGHTSIDEWALL + 25 && my[index].type == SPHERE)
			{
				collision[index] = 1;
			}
			if (pCurGo.pos.x >= FRONTWALL - 5 && pCurGo.pos.z <= RIGHTSIDEWALL + 10 && my[index].type == SPHERE)
			{
				collision[index] = 2;
			}
			if (pCurGo.pos.x >= FRONTWALL - 5 && pCurGo.pos.z >= LEFTSIDEWALL - 10 && my[index].type == SPHERE)
			{
				collision[index] = 3;
			}
			my[index].vel = pCurGo.vel;

			my[index].pos += deltaPosition;

			
				my[index].or2 += ((glm::cross(glm::vec3(0, 1, 0), deltaPosition) / 2.0f));

				rot[index] = (glm::cross(glm::vec3(0, 1, 0), deltaPosition) / 2.0f);
			


			if (deltaPosition.x <= 0.001f && deltaPosition.z <= 0.001f)
			{
				collision[index] = 0;
			}
			break;
		};

	}

	return;
}



