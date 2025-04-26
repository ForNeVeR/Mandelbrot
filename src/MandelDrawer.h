/* Header file for class that performs drawing operations. */
#ifndef MANDELDRAWER_H
#define MANDELDRAWER_H

class MandelMap;

class MandelDrawer
{
public:
    MandelDrawer(MandelMap *map, double center_x, double center_y, int from_y,
        int to_y);
    void setCenter(double x, double y);
    
    void calculate(double scale);

private:
    MandelMap *map;
    double center_x, center_y;
    int from_y, to_y;

    const static int MAX_ITERATION = 256;

    inline double scaleX(int x, double scale) const;
    inline double scaleY(int y, double scale) const;
};

#endif // MANDELDRAWER_H
