#include <iostream>
#include <vector>
#include "configuration.h"
using namespace std;

vector<vector<double>> nodes;

double kernel_function(double dis, double h);
double kernel_function_1dev(double dis, double h);
double kernel_function_2dev(double dis, double h);

void initial_3D_nodes()
{
	double loc_x, loc_y, loc_z;

	int _size = 2 * SUP_RADIUS_RATIO;

	loc_x = -_size;
	loc_y = -_size;
	loc_z = -_size;

	_size = _size * 2 + 1;

	for (int i = 0; i < _size; ++i)
	{
		loc_x += i;
		for (int j = 0; j < _size; ++j)
		{
			loc_y += j;
			for (int k = 0; k < _size; ++k)
			{
				loc_z += k;
				vector<double> tmp;
				tmp.push_back(loc_x); tmp.push_back(loc_y); tmp.push_back(loc_z);
				nodes.push_back(tmp);
			}
		}
	}

	for (int i = 0; i < nodes.size(); ++i)
	{
		for (int j = 0; j < nodes[i].size(); ++j) nodes[i][j] *= GRID_INTERVAL;
	}
}

void initial_2D_nodes()
{
	double loc_x, loc_y;

	int _size = 2 * SUP_RADIUS_RATIO;

	loc_x = -_size;
	loc_y = -_size;

	_size = _size * 2 + 1;

	for (int i = 0; i < _size; ++i)
	{
		loc_x += i;
		for (int j = 0; j < _size; ++j)
		{
			loc_y += j;

			vector<double> tmp;
			tmp.push_back(loc_x); tmp.push_back(loc_y);
			nodes.push_back(tmp);
		}
	}

	for (int i = 0; i < nodes.size(); ++i)
	{
		for (int j = 0; j < nodes[i].size(); ++j) nodes[i][j] *= GRID_INTERVAL;
	}
}

double cal_dens_3D(double mass)
{
	double tmp_density = 0.0;

	for (int i = 0; i < nodes.size(); ++i)
	{
		double dis_x, dis_y, dis_z;
		dis_x = 0.0 - nodes[i][0];
		dis_y = 0.0 - nodes[i][1];
		dis_z = 0.0 - nodes[i][2];

		tmp_density += kernel_function(dis_x, GRID_INTERVAL * SUP_RADIUS_RATIO);
		tmp_density += kernel_function(dis_y, GRID_INTERVAL * SUP_RADIUS_RATIO);
		tmp_density += kernel_function(dis_z, GRID_INTERVAL * SUP_RADIUS_RATIO);
	}

	tmp_density *= mass;

	return tmp_density;
}

double cal_dens_2D(double mass)
{
	double tmp_density = 0.0;

	for (int i = 0; i < nodes.size(); ++i)
	{
		double dis_x, dis_y;
		dis_x = 0.0 - nodes[i][0];
		dis_y = 0.0 - nodes[i][1];

		tmp_density += kernel_function(dis_x, GRID_INTERVAL * SUP_RADIUS_RATIO);
		tmp_density += kernel_function(dis_y, GRID_INTERVAL * SUP_RADIUS_RATIO);
	}

	tmp_density *= mass;

	return tmp_density;
}

void main()
{
	initial_2D_nodes();

	//double dens = cal_dens_3D(0.000035);

	double dens = cal_dens_2D(0.00115);

	system("pause");
}