/**
 * MCL.h
 *
 * @author Tucker Hermans
 */

#ifndef MCL_h_DEFINED
#define MCL_h_DEFINED
using namespace std;

// Includes
// STL
#include <vector>
#include <math.h>
#include <time.h> // for srand(time(NULL))
#include <cstdlib> // for MAX_RAND
// Local
#include "Observation.h"
#include "FieldConstants.h"

// Structs
// Pose Estimate
class PoseEst
{
public:
    float x;
    float y;
    float h;
};

// Odometery change
class MotionModel
{
public:
    float deltaF;
    float deltaL;
    float deltaR;
};

// Particle
class Particle
{
public:
    PoseEst pose;
    float weight;
    //BallEKF ball;
    //vector<EKF> opponents;
};

// Math Macros
#define DEG_TO_RAD (2. * M_PI) / 360.
#define RAD_TO_DEG 360. / (2. * M_PI)
#define FULL_CIRC 360
#define HALF_CIRC 180

// Constants
static const int M = 100; // Number of particles

// The Monte Carlo Localization class
class MCL
{
public:
    // Constructors & Destructors
    MCL();
    virtual ~MCL();

    // Core Functions
    void updateLocalization(MotionModel u_t, vector<Observation> z_t);

    // Getters
    /**
     * @return The current x esitamte of the robot
     */
    float getXEst() { return curEst.x;}

    /**
     * @return The current y esitamte of the robot
     */
    float getYEst() { return curEst.y;}

    /**
     * @return The current heading esitamte of the robot in radians
     */
    float getHEst() { return curEst.h;}

    /**
     * @return The current heading esitamte of the robot in degrees
     */
    float getHEstDeg() { return curEst.h * RAD_TO_DEG;}

    /**
     * @return The uncertainty associated with the x estimate of the robot.
     */
    float getXUncert() { return curUncert.x;}

    /**
     * @return The uncertainty associated with the y estimate of the robot.
     */
    float getYUncert() { return curUncert.y;}

    /**
     * @return The uncertainty associated with the robot's heading estimate.
     */
    float getHUncert() { return curUncert.h;}

    /**
     * @return The uncertainty associated with the robot's heading estimate.
     */
    float getHUncertDeg() { return curUncert.h * RAD_TO_DEG;}

    // Setters
    /**
     * @param xEst The current x esitamte of the robot
     */
    void setXEst(float xEst) { curEst.x = xEst;}

    /**
     * @param yEst The current y esitamte of the robot
     */
    void setYEst(float yEst) { curEst.y = yEst;}

    /**
     * @param hEst The current heading esitamte of the robot
     */
    void setHEst(float hEst) { curEst.h = hEst;}

    /**
     * @param uncertX The uncertainty of the x estimate of the robot.
     */
    void setXUncert(float uncertX) { curUncert.x = uncertX;}

    /**
     * @return uncertY The uncertainty of the y estimate of the robot.
     */
    void setYUncert(float uncertY) { curUncert.y = uncertY;}

    /**
     * @param uncertH The uncertainty of the robot's heading estimate.
     */
    void setHUncert(float uncertH) { curUncert.h = uncertH;}

private:
    // Class variables
    PoseEst curEst; // Current {x,y,h} esitamates
    PoseEst curUncert; // Associated {x,y,h} uncertainties (standard deviations)
    vector<Particle> X_t; // Current set of particles

    // Core Functions
    PoseEst updateOdometery(MotionModel u_t, PoseEst x_t);
    float updateMeasurementModel(vector<Observation> z_t, PoseEst x_t);
    void updateEstimates();

    // Helpers
    float determinePointWeight(Observation z, PoseEst x_t,
                               PointLandmark landmark);
    float determineLineWeight(Observation z, PoseEst x_t, LineLandmark _line);
    float getSimilarity(float r_d, float r_a, Observation &z);
};

#endif // _MCL_H_DEFINED