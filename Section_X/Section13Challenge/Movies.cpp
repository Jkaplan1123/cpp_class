/******************************************************************
 * Section 13 Challenge
 * Movies.h
 * 
 * Models a collection of Movies as a std::vector
 * 
 * ***************************************************************/
#include <iostream>
#include "Movies.h"

 /*************************************************************************
    Movies no-args constructor
**************************************************************************/
Movies::Movies() {
}

/*************************************************************************
    Movies destructor
**************************************************************************/
Movies::~Movies() {
}

  /*************************************************************************
    add_movie expects the name of the move, rating and watched count
    
    It will search the movies vector to see if a movie object already exists
    with the same name. 
    
    If it does then return false since the movie already exists
    Otherwise, create a movie object from the provided information
    and add that movie object to the movies vector and return true
    *********************************************************************/
bool Movies::add_movie(std::string name, std::string rating, int watched) {
    // you implement this method

    if(! have_watched(name)){
        movies.push_back(Movie{name, rating, watched});
        return true;
    }
    return false;
}

 /*************************************************************************
    increment_watched expects the name of the move to increment the
    watched count
    
    It will search the movies vector to see if a movie object already exists
    with the same name. 
    If it does then increment that objects watched by 1 and return true.

    Otherwise, return false since then no movies object with the movie name
    provided exists to increment
    *********************************************************************/
bool Movies::increment_watched(std::string name) {
   // you implement this method

    int idx {0};
    idx = find_movie(name);
    if (idx != -1){
        (movies.at(idx)).increment_watched();
        return true;
    }
   
    else {
        return false;
    }
}

/*************************************************************************
    have_watched expects the name of the movie as a string. It searches the movies vector to see if a movie object already exists with the same name. If it finds it, then it returns the index. Otherwise, it returns -1.
    *********************************************************************/
int Movies::find_movie(const std::string name) const {

    if(have_watched(name)){
        int idx {0};
        while ((movies.at(idx)).get_name() != name){
            idx++;
        }
        
        return idx;
    }    

    else{
        // std::cout << "Error: Movie not in list of movies" << std::endl;
        return -1;
    }
}

/*************************************************************************
    have_watched expects the name of the movie. It searches the movies 
    vector to see if a movie object already exists with the same name. 
    If it finds it, then it returns true. Otherwise, it returns false.
    *********************************************************************/
bool Movies::have_watched(const std::string name) const {
    for (auto movie : movies){
        if (movie.get_name() == name){
            return true;
        }
    }

    return false;
}

/*************************************************************************
    display
    
    display all the movie objects in the movies vector.
    for each movie call the movie.display method so the movie
    object displays itself
    *********************************************************************/
void Movies::display() const {
   // You implement this method

    if (movies.size() != 0){
        std::cout << "\nMovies Watched:" << std::endl;
        std::cout << "--------------------" << std::endl;
        for (auto movie : movies){
            movie.display();
        }

        std::cout << std::endl;
    }

    else{
        std::cout << "No movies watched" << std::endl;
    }
}