
//
//  main.cpp
//  LLTemplate
//
//  Created by James Shockey on 12/6/16.
//  Copyright © 2016 James Shockey. All rights reserved.
//


/*
 *
 *	Linked List lab.
 *	- Build a library for singly linked list.
 *	- Replace the airport array in main with a Linked List.
 *  - sort the array. 
 *	
 */


#include <iostream>
#include <fstream>
#include <cmath> 
#include <string>
#include "slist.h"
using namespace std;

class Airport
{
public:
    char    code[5];
    double   longitude;
    double   latitude;
};



void simpleSortTotal(slist::slist* s[], int c);
slist::Node* mergeLists(slist::Node *a, slist::Node *b);
void mergeSort(slist::slist* arr);
void splitLists(slist::Node* h, slist::Node** p1, slist::Node** p2);

double distanceEarth(double lat1d, double lon1d, double lat2d, double lon2d);

// Reference point: KAUS,large_airport,Austin Bergstrom International Airport,-97.66989899,30.19449997,542,NA,US,US-TX,Austin,KAUS,AUS,AUS,

void selectionSort(slist::slist* arr) {
  Airport* refPort = new Airport();
  refPort->code[0] = 'K';
  refPort->code[1] = 'A';
  refPort->code[2] = 'U';
  refPort->code[3] = 'S';
  refPort->longitude = -97.66989899;
  refPort->latitude = 30.19449997;
  
  slist::Node* temp = arr->head;

  while (temp) {
    cout << ".";
    slist::Node* min = temp;
    slist::Node* r = temp->next;

    while (r) {
      Airport minP = *(Airport *) (min->data);
      Airport rP = *(Airport *) (r->data);
      double distMin = distanceEarth(minP.longitude, minP.latitude , refPort->longitude, refPort->latitude);
      double distR = distanceEarth(rP.longitude, rP.latitude , refPort->longitude, refPort->latitude);

      if (distMin > distR) { min = r; }

      r = r->next;
    }

    Airport* x = (Airport *) (temp->data);
    temp->data = min->data;
    min->data = x;
    temp = temp->next;
  }
}


int main()
{
  ifstream infile;
  int i=0;
  char cNum[10];
  slist::slist airportArr = slist::slist();			// Replace array with Linked List
  int   airportCount = 0;
  //Airport* a[13500];
  char junk[225];
  // 13 columns
  
  infile.open ("airport-codes_US.csv", ifstream::in);
  if (infile.is_open())
  {
    int   c=0;
    while (infile.good())
    {
      //cout << "----------------------------------- Reading In... " << endl;
      Airport* airport1 = new Airport();
      // Read in Airport Code (1)
      infile.getline(airport1->code, 256, ','); // (1)
      
      infile.getline(junk, 256, ','); // (2)
      infile.getline(junk, 256, ','); // (3)

      // Read in Longitude
      infile.getline(cNum, 256, ','); // (4)
      airport1->longitude = atof(cNum);
      
      // Read in Latitude
      infile.getline(cNum, 256, ','); // (5)
      airport1->latitude = atof(cNum);

      infile.getline(junk, 256, ','); // (6)
      infile.getline(junk, 256, ','); // (7)
      infile.getline(junk, 256, ','); // (8)
      infile.getline(junk, 256, ','); // (9)
      infile.getline(junk, 256, ','); // (10)
      infile.getline(junk, 256, ','); // (11)
      infile.getline(junk, 256, ','); // (12)
      infile.getline(junk, 256, '\n'); // (13)

      //cout << " line " << c+1 << endl;
      
      airportArr.add(airport1);

      if ((c % 1000 == 0)) {
        //slist::Node * temp1 = airportArr.slist::get(c); // imposter
        slist::Node * temp1 = airportArr.slist::tail;
        Airport* Air1 = ((Airport *)temp1->data);
        cout << Air1->code << " long: " << Air1->longitude << " lat: " << Air1->latitude <<  endl;
        cout << " line " << c << endl;
      } 
      /*
      if (!(c % 1000)) {
          cout << airportArr[c]->code << " long: " << airportArr[c]->longitude << " lat: " << airportArr[c]->latitude <<  endl;
          cout << airportArr[c+1]->code << endl; //" long: " << airportArr[c+1]->longitude << " lat: " << airportArr[c+1]->latitude <<  endl;  
      }
      */
      i++;
      c++;
    }
    
    airportCount = c-1;
    infile.close();

    //simpleSortTotal(&airportArr, c);
    //mergeSort(&airportArr);
    selectionSort(&airportArr);
    slist::Node * temp1 = airportArr.slist::tail;
    Airport* Air1 = ((Airport *)temp1->data);
    cout << "LAST : " << Air1->code << endl;

    Airport* refPort = new Airport();
    refPort->code[0] = 'K';
    refPort->code[1] = 'A';
    refPort->code[2] = 'U';
    refPort->code[3] = 'S';
    refPort->longitude = -97.66989899;
    refPort->latitude = 30.19449997;

    slist::Node * currentN = airportArr.slist::head;
    for (int c=0; c < airportCount-1; c++) {
      currentN = currentN->next;
      Airport* current = ((Airport *)currentN->data);
      if (distanceEarth(current->longitude, current->latitude , refPort->longitude, refPort->latitude) <= 100.0) {
        cout << current->code << ", " << current->longitude << ", " << current->latitude << endl;
      } else {
        break;
      }   
    }
  } else { cout << "Error opening file"; }   
} // end of main

#define pi 3.14159265358979323846
#define earthRadiusKm 6371.0

// This function converts decimal degrees to radians
double deg2rad(double deg) {
  return (deg * pi / 180);
}

//  This function converts radians to decimal degrees
double rad2deg(double rad) {
  return (rad * 180 / pi);
}

/**
 * Returns the distance between two points on the Earth.
 * Direct translation from http://en.wikipedia.org/wiki/Haversine_formula
 * @param lat1d Latitude of the first point in degrees
 * @param lon1d Longitude of the first point in degrees
 * @param lat2d Latitude of the second point in degrees
 * @param lon2d Longitude of the second point in degrees
 * @return The distance between the two points in kilometers
 */
double distanceEarth(double lat1d, double lon1d, double lat2d, double lon2d) {
  double lat1r, lon1r, lat2r, lon2r, u, v;
  lat1r = deg2rad(lat1d);
  lon1r = deg2rad(lon1d);
  lat2r = deg2rad(lat2d);
  lon2r = deg2rad(lon2d);
  u = sin((lat2r - lat1r)/2);
  v = sin((lon2r - lon1r)/2);
  return 2.0 * earthRadiusKm * asin(sqrt(u * u + cos(lat1r) * cos(lat2r) * v * v));
}

/*
	Provide sort routine on linked list

slist::Node* mergeLists(slist::Node *a, slist::Node *b) {
  slist::Node* result = NULL;

  if (a == NULL) {
    return a;
  } else if (b == NULL) { return b; }
  
  
  Airport* refPort = new Airport();
  refPort->code[0] = 'K';
  refPort->code[1] = 'A';
  refPort->code[2] = 'U';
  refPort->code[3] = 'S';
  refPort->longitude = -97.66989899;
  refPort->latitude = 30.19449997;
  
  Airport aP = *(Airport *) (a->data);
  Airport bP = *(Airport *) (b->data);
  double distA = distanceEarth(aP.longitude, aP.latitude , refPort->longitude, refPort->latitude);
  double distB = distanceEarth(bP.longitude, bP.latitude , refPort->longitude, refPort->latitude);

  if (distA <= distB) {
    result = a;
    result->next = mergeLists(a->next, b);
  } else {
    result = b;
    result->next = mergeLists(a, b->next);
  }
  return result;
}

void splitLists(slist::Node* h, slist::Node** p1, slist::Node** p2) {
  slist::Node* a;
  slist::Node* b;
  b = h;
  a = h->next;

  while (a != NULL) {
    a = a->next;
    if (a != NULL) {
      b = b->next;
      a = a->next;
    }
  }

  *p1 = h;
  *p2 = b->next;
  b->next = NULL;
}

void mergeSort(slist::slist* arr)
{
  slist::Node* head1 = arr->head;
  slist::Node* p1;
  slist::Node* p2;

  if ((head1 == NULL) || (head1->next == NULL)) { return; }

  splitLists(head1, &p1, &p2);
  mergeSort(&p1);
  mergeSort(&p2);

  arr->head = mergeLists(p1, p2);
  
}*/