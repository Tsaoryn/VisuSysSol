#include "glimac/Sun.hpp"
#include <iostream>
namespace glimac{
    
    void Sun::initPlanets(char* path){
        //don't forget to change the path in path.txt when you change your location
        std::list<std::shared_ptr<Moon>> moons = {};
        
        ifstream file("../GLImac-Template/assets/ressources/path.txt");
        std::string subPath;
        getline(file, subPath);
 
        
        std::string pathMoon = subPath+"/assets/textures/MoonMap.jpg";
        std::shared_ptr<Moon> moon = std::shared_ptr<Moon>(new Moon(path,pathMoon,384400.0f,0.0549f,3475.0f,5.145f,12756.0f,1));
        
        std::shared_ptr<Moon> Phobos = std::shared_ptr<Moon>(new Moon(path,pathMoon,9378.0f,0.0151f,22.5f,1.08f,6792.0f,1));
        std::shared_ptr<Moon> Demios = std::shared_ptr<Moon>(new Moon(path,pathMoon,23459.0f,0.0005f,12.0f,1.79f,6792.0f,(23459.0f/2-9378.0f/2)/9378.0f));
        
        std::shared_ptr<Moon> Io = std::shared_ptr<Moon>(new Moon(path,pathMoon,421700.0f,0.004f,3643.0f,0.04f,142984.0f,1));
        std::shared_ptr<Moon> Europa = std::shared_ptr<Moon>(new Moon(path,pathMoon,671030.0f,0.009f,3122.0f,0.47f,142984.0f,(671030.0f/2.0f-421700.0f/2.0f)/421700.0f));
        std::shared_ptr<Moon> Ganymede = std::shared_ptr<Moon>(new Moon(path,pathMoon,1070410.0f,0.001f,5262.0f,0.18f,142984.0f,(1070410.0f/2.0f-421700.0f/2.0f)/421700.0f));
        std::shared_ptr<Moon> Callisto = std::shared_ptr<Moon>(new Moon(path,pathMoon,1882710.0f,0.007f,4821.0f,0.19f,142984.0f,(1882710.0f/2.0f-421700.0f/2.0f)/421700.0f));
        
        
        std::shared_ptr<Moon> Mimas = std::shared_ptr<Moon>(new Moon(path,pathMoon,185520.0f,0.0202f,392.0f,1.53f,120536.0f,1));
        std::shared_ptr<Moon> Enceladus = std::shared_ptr<Moon>(new Moon(path,pathMoon,238020.0f,0.0045f,498.0f,0.0f,120536.0f,(238020.0f/2.0f-185520.0f/2.0f)/185520.0f));
        std::shared_ptr<Moon> Tethys = std::shared_ptr<Moon>(new Moon(path,pathMoon,294660.0f,0.0f,1060.0f,1.86f,120536.0f, (294660.0f/2.0f-185520.0f/2.0f)/185520.0f));
        std::shared_ptr<Moon> Dione = std::shared_ptr<Moon>(new Moon(path,pathMoon,377400.0f,0.0022f,1120.0f,0.02f,120536.0f, (377400.0f/2.0f-185520.0f/2.0f)/185520.0f));
        std::shared_ptr<Moon> Rhea = std::shared_ptr<Moon>(new Moon(path,pathMoon,527040.0f,0.0010f,1530.0f,0.35f,120536.0f, (527040.0f/2.0f-185520.0f/2.0f)/185520.0f));
        std::shared_ptr<Moon> Titan = std::shared_ptr<Moon>(new Moon(path,pathMoon,1221830.0f,0.0292f,5150.0f,0.33f,120536.0f, (1221830.0f/2.0f-185520.0f/2.0f)/185520.0f));
        std::shared_ptr<Moon> Hyperion = std::shared_ptr<Moon>(new Moon(path,pathMoon,1481100.0f,0.1042f,286.0f,0.43f,120536.0f, (1481100.0f/2.0f-185520.0f/2.0f)/185520.0f));
        std::shared_ptr<Moon> Iapetus = std::shared_ptr<Moon>(new Moon(path,pathMoon,3561300.0f,0.0283f,1460.0f,14.72f,120536.0f, (3561300.0f/2.0f-185520.0f/2.0f)/185520.0f));
        
        
        std::shared_ptr<Moon> Miranda = std::shared_ptr<Moon>(new Moon(path,pathMoon,129900.0f,0.0013,472.0f,4.34f,51118.0f,1));
        std::shared_ptr<Moon> Ariel = std::shared_ptr<Moon>(new Moon(path,pathMoon,199900.0f,0.0012f,1158.0f,0.04f,51118.0f,(199900.0f/2.0f-129900.0f/2.0f)/129900.0f));
        std::shared_ptr<Moon> Umbriel = std::shared_ptr<Moon>(new Moon(path,pathMoon,266000.0f,0.0039f,1169.0f,0.13f,51118.0f,(266000.0f/2.0f-129900.0f/2.0f)/129900.0f));
        std::shared_ptr<Moon> Titania = std::shared_ptr<Moon>(new Moon(path,pathMoon,436300.0f,0.0011f,1577.0f,0.08,51118.0f,(436300.0f/2.0f-129900.0f/2.0f)/129900.0f));
        std::shared_ptr<Moon> Oberon = std::shared_ptr<Moon>(new Moon(path,pathMoon,583500.0f,0.0014,1523.0f,0.07f,51118.0f,(583500.0f/2.0f-129900.0f/2.0f)/129900.0f));
        
        std::shared_ptr<Moon> Triton = std::shared_ptr<Moon>(new Moon(path,pathMoon,354760.0f,0.000016f,2707.0f,157.345f,49528.0f,1));
        std::shared_ptr<Moon> Nereid = std::shared_ptr<Moon>(new Moon(path,pathMoon,5513400.0f,0.7512,340.0f,7.23f,49528.0f,(5513400.0f/2.0f-354760.0f/2.0f)/354760.0f));
        
        std::shared_ptr<Moon> Charon = std::shared_ptr<Moon>(new Moon(path,pathMoon,19591.0f,0.0f,1212.0f,0.00005f,2370.0f,1));
                
        std::shared_ptr<Planet> Mercury = std::shared_ptr<Planet>(new Planet(path,subPath+"/assets/textures/MercuryMap.jpg", "", moons, false, false,69800000.0f,46000000.0f, 4879.0f, 88.0f, 4222.6f,7.0f,0.205f,1,0.0f,_diameter));
        std::shared_ptr<Planet> Venus = std::shared_ptr<Planet>(new Planet(path,subPath+"/assets/textures/VenusMap.jpg", "", moons, false, false,108900000.0f,107500000.0f, 12104.0f, 224.7f, 2802.0f,3.4f,0.007f,2,0.0f,_diameter));
        moons.push_back(moon);
        std::shared_ptr<Planet> Earth = std::shared_ptr<Planet>(new Planet(path,subPath+"/assets/textures/EarthMap.jpg", subPath+"/assets/textures/CloudMap.jpg", moons, true, false,152100000.0f,147100000.0f, 12756.0f, 365.2f,24.0f,0.0f,0.017,3,0.0f,_diameter));
        moons.clear();
        moons.push_back(Phobos);
        moons.push_back(Demios);
        std::shared_ptr<Planet> Mars = std::shared_ptr<Planet>(new Planet(path,subPath+"/assets/textures/MarsMap.jpg", "", moons, false, false,249200000.0f,206600000.0f, 6792.0f, 687.0f,24.7f,1.9f,0.094f,4,0.0f,_diameter)) ;
        moons.clear();
        moons.push_back(Callisto);
        moons.push_back(Ganymede);
        moons.push_back(Europa);
        moons.push_back(Io);
        std::shared_ptr<Planet> Jupiter = std::shared_ptr<Planet>(new Planet(path,subPath+"/assets/textures/JupiterMap.jpg", "", moons, false, false,816600000.0f,740500000.0f, 142984.0f,4331.0f,9.9f,1.3f,0.049f,6,0.0f,_diameter)) ;
        moons.clear();
        moons.push_back(Mimas);
        moons.push_back(Enceladus);
        moons.push_back(Tethys);
        moons.push_back(Dione);
        moons.push_back(Rhea);
        moons.push_back(Titan);
        moons.push_back(Hyperion);
        moons.push_back(Iapetus);
        std::shared_ptr<Planet> Saturn = std::shared_ptr<Planet>(new Planet(path,subPath+"/assets/textures/SaturnMap.jpg", subPath+"/assets/textures/saturnringcolour.jpg", moons, false, true, 1514500000.0f,1352600000.0f, 120536.0f, 10747.0f,10.7f,2.5f,0.057f,9,0.0f,_diameter)) ;
        moons.clear();
        moons.push_back(Ariel);
        moons.push_back(Umbriel);
        moons.push_back(Titania);
        moons.push_back(Oberon);
        moons.push_back(Miranda);
        std::shared_ptr<Planet> Uranus = std::shared_ptr<Planet>(new Planet(path,subPath+"/assets/textures/UranusMap.jpg", subPath+"/assets/textures/uranusringcolour.jpg", moons, false, true,3003600000.0f,2741300000.0f, 51118.0f, 30589.0f,17.2f, 0.8f,0.046f,12,0.0f,_diameter)) ;
        moons.clear();
        moons.push_back(Triton);
        moons.push_back(Nereid);
        std::shared_ptr<Planet> Neptune = std::shared_ptr<Planet>(new Planet(path,subPath+"/assets/textures/NeptuneMap.jpg", "", moons, false, false,4545700000.0f,4444500000.0f, 49528.0f, 59800.0f,16.1f,1.8f,0.011f,20,0.0f,_diameter)) ;
        moons.clear();
        moons.push_back(Charon);
        std::shared_ptr<Planet> Pluto = std::shared_ptr<Planet>(new Planet(path,subPath+"/assets/textures/PlutoMap.jpg", "", moons, false, false,7375900000.0f,4436800000.0f, 2370.0f, 90560.0f,153.3f,17.2f,0.244f,30,0.0f,_diameter));
        
        _planets.push_back(Mercury);
        _planets.push_back(Venus);
        _planets.push_back(Earth);
        _planets.push_back(Mars);
        _planets.push_back(Jupiter);
        _planets.push_back(Saturn);
        _planets.push_back(Uranus);
        _planets.push_back(Neptune);
        _planets.push_back(Pluto);
    }

    void Sun::drawSystem(float t, std::shared_ptr<Camera> camera){
       _drawer.drawPlanet(t, camera, false, false, 10.0f, 1.0f);
        for (auto planet : _planets) 
            planet->drawPlanet(_diameter, t, camera);
    }
    
    void Sun::drawOnePlanet(int numPlanet, float t, std::shared_ptr<Camera> camera){
		_planets[numPlanet]->drawPlanetAlone(_diameter, t, camera);
	}
    
    void Sun::deleteTextures(){
        _drawer.deleteTextures(false);
        for(auto planet : _planets)
            planet->deleteTextures();
    }
}
