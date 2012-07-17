#ifndef FOOTEST_H
#define FOOTEST_H

class FooTest : public Test
{
    public:
    FooTest() { 

	    // Define the ground body.
	    b2BodyDef groundBodyDef[4];
	    groundBodyDef[0].position.Set(0.0f, 2.7f);      //top
	    groundBodyDef[1].position.Set(0.0f, -2.7f);     //bottom
	    groundBodyDef[2].position.Set(-3.7f, 0.0f);     //left
	    groundBodyDef[3].position.Set(3.7f, 0.0f);      //right

	    // Call the body factory which allocates memory for the ground body
	    // from a pool and creates the ground box shape (also from a pool).
	    // The body is also added to the world.
	    b2Body* groundBody[4];
	    for(unsigned int i = 0; i < 4; i += 1){
	        groundBody[i] = m_world->CreateBody(&groundBodyDef[i]);
	    }
	
	    // Define the ground box shape.
	    b2PolygonShape groundBox[4];

	    // The extents are the half-widths of the box.
	    groundBox[0].SetAsBox(3.7f, 0.003f);
	    groundBox[1].SetAsBox(3.7f, 0.003f);
	    groundBox[2].SetAsBox(0.003f, 2.7f);
	    groundBox[3].SetAsBox(0.003f, 2.7f);

	    // Add the ground fixture to the ground body.
	    for(unsigned int i = 0; i < 4; i += 1){
	        groundBody[i]->CreateFixture(&groundBox[i], 0.0f);
	    }
	
	    // Define the dynamic body. We set its position and call the body factory.
	    b2BodyDef bodyDef[6];
	    for(unsigned int i = 0; i < 6; i += 1){
	        bodyDef[i].type = b2_dynamicBody;
	    }
	
	    bodyDef[0].position.Set(1.0f, 2.0f);
	    bodyDef[1].position.Set(1.0f, 0.0f);
	    bodyDef[2].position.Set(1.0f, -2.0f);
	    bodyDef[3].position.Set(2.0f, 1.0f);
	    bodyDef[4].position.Set(2.0f, -1.0f);
	    bodyDef[5].position.Set(3.0f, 0.0f);
	
	    b2Body* body[6];
	    for(unsigned int i = 0; i < 6; i += 1){
	        body[i] = m_world->CreateBody(&bodyDef[i]);
	        b2Vec2 pos = body[i]->GetPosition();
            body[i]->SetTransform(pos, 90.0);
	    }

	    // Define another box shape for our dynamic body.
	    b2PolygonShape dynamicBox;
	    dynamicBox.SetAsBox(0.09f, 0.09f);
	    
	    b2Vec2 vertices[19];
        vertices[0].Set(-0.090000f, 0.000000f);
        vertices[1].Set(-0.087385f, -0.021538f);
        vertices[2].Set(-0.079691f, -0.041825f);
        vertices[3].Set(-0.067366f, -0.059681f);
        vertices[4].Set(-0.051126f, -0.074069f);
        vertices[5].Set(-0.031914f, -0.084151f);
        vertices[6].Set(-0.010848f, -0.089344f);
        vertices[7].Set(0.010848f, -0.089344f);
        vertices[8].Set(0.031914f, -0.084151f);
        vertices[9].Set(0.051126f, -0.074069f);
        vertices[10].Set(0.067366f, -0.059681f);
        vertices[11].Set(0.079691f, -0.041825f);
        vertices[12].Set(0.087385f, -0.021538f);
        vertices[13].Set(0.087385f, 0.021538f);
        vertices[14].Set(0.079691f, 0.041825f);
        vertices[15].Set(0.067366f, 0.059681f);
        vertices[16].Set(-0.067366f, 0.059681f);
        vertices[17].Set(-0.079691f, 0.041825f);
        vertices[18].Set(-0.087385f, 0.021538f);
        int32 count = 19;

        b2PolygonShape polygon;
        polygon.Set(vertices, count);
        

	    // Define the dynamic body fixture.
	    b2FixtureDef fixtureDef;
	    b2FixtureDef fixtureDefTri;
	    
	    fixtureDef.shape = &dynamicBox;
        fixtureDefTri.shape = &polygon;
        
	    // Set the box density to be non-zero, so it will be dynamic.
	    fixtureDef.density = 1.0f;
        fixtureDefTri.density = 1.0f;
        
	    // Override the default friction.
	    fixtureDef.friction = 0.3f;
        fixtureDefTri.friction = 0.3f;

	    // Add the shape to the body.
	    for(unsigned int i = 0; i < 6; i += 1){
	        body[i]->CreateFixture(&fixtureDefTri);
	    }
    }

    void Step(Settings* settings)
    {
        //run the default physics and rendering
        Test::Step(settings); 

        //show some text in the main screen
        m_debugDraw.DrawString(5, m_textLine, "Now we have a foo test");
        m_textLine += 15;
    }

    static Test* Create()
    {
        return new FooTest;
    }
};

#endif
