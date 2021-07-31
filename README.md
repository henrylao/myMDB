# Context Indexing Movie Search Engine
This program was written for DeAnza's CS301 Data Structures class in 2019 as a final project. Constraints required utilization of an in-house implementation of template data structures used in the development of the application. The application is a CLI interface for interacting with a database of movies using the database's search engine.

# Data Structures Used
* Singly Linked List
* Stack
* HashTable (Quadratic Probing)
* Binary Search Tree


# How It Works
<div>
<img src="https://github.com/henrylao/movie-search-engine/blob/master/images/programFlow.png" width="642" height="361"/>
</div>

# Create
## (1) Build the list of movies 
1. load each row denoting a movie entry and its attributes
2. create the movie entry and add into the list collection
	
## (2) Create the hashtabe of movies
1. Use movie ID attribute as the key
2. Preprocess the ID cleaning out any unwanted characters 
3. Add the movie into the database using the preprocessed key and the movie as the value
<div>
<img src="https://github.com/henrylao/movie-search-engine/blob/master/images/movieDB.png" width="642" height="361"/>
</div>

## (3) Create the search engine
* Using the list of movies, create a map of bsts. 
    * __NOTE__ Index of bst was maintained lexically. 
* BST entries containing __keywords__ associated with a __movie__ such that that the __first character__ of each tokenized keyword pertaining to a movie signifies a key in the dictionary
    * __NOTE__: tokenized words are the movie attributes such as the movie name, genre, year released, runtime, and id
        - more attributes could have included the cast as well as production -- at the bare minimum there are atleast 5 attributes resulting in 5 keywords
        - this was the largest computational cost when spinning up the application since it uses a nested loop resulting in an average __O(n^2)__ insertion time
    
<div>
<img src="https://github.com/henrylao/movie-search-engine/blob/master/images/contextIndexSearch.png" width="642" height="361"/>
</div>

### Start Up Statistics (Small Dataset)       
| Process                            | Time       |
|------------------------------------|------------|
| List of Movies Generation Time     | 0.069353s  |
| Movie Load From List to Table Time | 0.0349641s |
| Tabled BST Search Engine Time      | 2.73182s   |

### Movie Table Statistics          
| Metrics              | Values |
|----------------------|--------|
| Occupancy            | 507    |
| Capacity             | 1277   |
| Load Factor          | 39.7%  |
| Number of Collisions | 166    |


### Tabled BST Search Engine Statistics     
| Metrics              | Values |
|----------------------|--------|
| Occupancy            | 41     |
| Capacity             | 521    |
| Load Factor          | 7.869% |
| Number of Collisions | 0      |


# Read
Reading movies based on relevance of a user's keyword search
1. Preprocess the keyword(s) search entry into tokenized list
2. Loop LV 1: For each starting character of a tokenized user entry get the associated BST
    at __O(1)__ and search for the associated keyword BST node __O(logn)__
    - __NOTE__ user keyword searches are usually short, this would have many issues if there were too many keywords 
3. Loop LV 2: For each __keyword-node__ containing a list of movies, create a tally value of 1 for each movie associated keyword MovieID incrementing the tally for each existing movieID __O(n^2)__
4. Sort movies based upon their tallied keyword relevance ie `"how many keyword hits did each movie have?"` and return list of movies sorted by relevance measured by the set of tokenized keywords of a user search entry


# References:
* Context Index Searching: https://citeseerx.ist.psu.edu/viewdoc/download?doi=10.1.1.309.9686&rep=rep1&type=pdf
* IMDB Dataset: https://www.imdb.com/interfaces/
