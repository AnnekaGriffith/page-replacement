#include<bits/stdc++.h>
#include <iostream>     // std::cout
#include <algorithm>    // std::random_shuffle
#include <vector>       // std::vector
#include <ctime>        // std::time
#include <fstream>
#include <string>
#include <array>
#include <cstdlib>      // std::rand, std::srand
using namespace std;

vector <int> randomPageRef() 
{
    //randomPage generator
    srand ( unsigned ( std::time(0) ) );
    vector<int> myvector;

      // set some values:
    for (int i=0; i<100; ++i) 
    { 
          myvector.push_back(rand() % 50);
    } 
    return myvector;
}
vector <int> convertStrtoVector(string str) 
{ 
    //uses stringstream to copy char elements the ',' is used to break up the int values within the string
    vector<int> pages;
    stringstream ss(str);
    int n;
    char ch;

    while(ss >> n) {
        if(ss >> ch)
            pages.push_back(n);
        else
            pages.push_back(n);
    }
    return pages;
} 
int FIFO(string pages, int capacity) 
{ 
	// To represent set of current pages. We use 
	// an unordered_set so that we quickly check 
	// if a page is present in set or not 
	unordered_set<int> s; 

	// To store the pages in FIFO manner 
	queue<int> indexes; 
        //creates array called pagesA and copies the pagesV vector into it
        vector <int> pagesV = convertStrtoVector(pages);

        int pagesA[pagesV.size()];
        copy(pagesV.begin(), pagesV.end(), pagesA);

	// Start from initial page 
	int page_faults = 0; 
	for (int i=0; i<100; i++) 
	{ 
		// Check if the set can hold more pages 
		if (s.size() < capacity) 
		{ 
			// Insert it into set if not present 
			// already which represents page fault 
			if (s.find(pagesA[i])==s.end()) 
			{ 
				// Insert the current page into the set 
				s.insert(pagesA[i]); 

				// increment page fault 
				page_faults++; 

				// Push the current page into the queue 
				indexes.push(pagesA[i]); 
			} 
		} 

		// If the set is full then need to perform FIFO 
		// i.e. remove the first page of the queue from 
		// set and queue both and insert the current page 
		else
		{ 
			// Check if current page is not already 
			// present in the set 
			if (s.find(pagesA[i]) == s.end()) 
			{ 
				// Store the first page in the 
				// queue to be used to find and 
				// erase the page from the set 
				int val = indexes.front(); 
				
				// Pop the first page from the queue 
				indexes.pop(); 

				// Remove the indexes page from the set 
				s.erase(val); 

				// insert the current page in the set 
				s.insert(pagesA[i]); 

				// push the current page into 
				// the queue 
				indexes.push(pagesA[i]); 

				// Increment page faults 
				page_faults++; 
			} 
		} 
	} 

	return page_faults; 
} 
int LRU(string pages, int capacity) 
{ 
    // To represent set of current pages. We use 
    // an unordered_set so that we quickly check 
    // if a page is present in set or not 
    unordered_set<int> s; 
  
    // To store least recently used indexes 
    // of pages. 
    unordered_map<int, int> indexes; 
    
    vector <int> pagesV = convertStrtoVector(pages);
    //creates array called pagesA and copies the pagesV vector into it
    int pagesA[pagesV.size()];
    copy(pagesV.begin(), pagesV.end(), pagesA);
    // Start from initial page 
    int page_faults = 0; 
    for (int i=0; i<100; i++) 
    { 
        // Check if the set can hold more pages 
        if (s.size() < capacity) 
        { 
            // Insert it into set if not present 
            // already which represents page fault 
            if (s.find(pagesA[i])==s.end()) 
            { 
                s.insert(pagesA[i]); 
  
                // increment page fault 
                page_faults++; 
            } 
  
            // Store the recently used index of 
            // each page 
            indexes[pagesA[i]] = i; 
        } 
  
        // If the set is full then need to perform lru 
        // i.e. remove the least recently used page 
        // and insert the current page 
        else
        { 
            // Check if current page is not already 
            // present in the set 
            if (s.find(pagesA[i]) == s.end()) 
            { 
                // Find the least recently used pages 
                // that is present in the set 
                int lru = INT_MAX, val; 
                for (auto it=s.begin(); it!=s.end(); it++) 
                { 
                    if (indexes[*it] < lru) 
                    { 
                        lru = indexes[*it]; 
                        val = *it; 
                    } 
                } 
  
                // Remove the indexes page 
                s.erase(val); 
  
                // insert the current page 
                s.insert(pagesA[i]); 
  
                // Increment page faults 
                page_faults++; 
            } 
  
            // Update the current page index 
            indexes[pagesA[i]] = i; 
        } 
    } 
  
    return page_faults; 
} 
bool search(int key, vector<int>& fr) 
{ 
    for (int i = 0; i < fr.size(); i++) 
        if (fr[i] == key) 
            return true; 
    return false; 
} 
  
// Function to find the frame that will not be used 
// recently in future after given index in pg[0..pn-1] 
int predict(int pg[], vector<int>& fr, int index) 
{ 
    
    // Store the index of pages which are going 
    // to be used recently in future 
    int res = -1, farthest = index; 
    for (int i = 0; i < fr.size(); i++) { 
        int j; 
        for (j = index; j < 100; j++) { 
            if (fr[i] == pg[j]) { 
                if (j > farthest) { 
                    farthest = j; 
                    res = i; 
                } 
                break; 
            } 
        } 
  
        // If a page is never referenced in future, 
        // return it. 
        if (j == 100) 
            return i; 
    } 
  
    // If all of the frames were not in future, 
    // return any of them, we return 0. Otherwise 
    // we return res. 
    return (res == -1) ? 0 : res; 
} 
  
int OPT(string pages, int capacity) 
{ 
    // Create an array for given number of 
    // frames and initialize it as empty. 
    vector<int> fr; 
    vector <int> pagesV = convertStrtoVector(pages);
    //creates array called pagesA and copies the pagesV vector into it
    int pagesA[pagesV.size()];
    copy(pagesV.begin(), pagesV.end(), pagesA);
    // Traverse through page reference array 
    // and check for miss and hit. 
    int hit = 0; 
    for (int i = 0; i < 100; i++) { 
  
        // Page found in a frame : HIT 
        if (search(pagesA[i], fr)) { 
            hit++; 
            continue; 
        } 
  
        // Page not found in a frame : MISS 
  
        // If there is space available in frames. 
        if (fr.size() < capacity) 
            fr.push_back(pagesA[i]); 
  
        // Find the page to be replaced. 
        else { 
            int j = predict(pagesA, fr, i + 1); 
            fr[j] = pagesA[i]; 
        } 
    } 
    return 100 - hit; 
} 
// Driver code 
int main() 
{ 
    stringstream ss;
    stringstream ssSpace;
    vector <int> v = randomPageRef();
    //copies the vector v into the ss stringstream 
    copy( v.begin(), v.end(), ostream_iterator<int>(ss, ","));
    copy( v.begin(), v.end(), ostream_iterator<int>(ssSpace, " "));
    string s = ss.str();
    string sSpace = ssSpace.str();
    s = s.substr(0, s.length()-1);
    cout << "Random page reference string: '" << s << "'" << endl<< endl;
    cout << "____FIFO Page Faults____"<< endl;
    
    for (int i=1; i<31; ++i) 
    {
        int capacity = i;
        int FIFO_Faults = FIFO(s, capacity);
        
        cout << "FIFO w/page "<< i << " fames: " << FIFO_Faults << endl;
    }
    
    cout<< endl;
    cout << "____LRU Page Faults____" << endl;
    for (int i=1; i<31; ++i) 
    {
        int capacity = i;
        int LRU_Faults = LRU(s, capacity);
        
        cout << "LRU w/page "<< i << " fames: " << LRU_Faults << endl;
    }
    
    cout<< endl;
    cout << "____OPT Page Faults____"<< endl;
    for (int i=1; i<31; ++i) 
    {
        int capacity = i;
        int OPT_Faults = OPT(s, capacity);

        cout << "OPT w/page "<< i << " fames: " << OPT_Faults << endl;
    }

    cout << "Random page reference string w/out commas: '" << sSpace << "'" ;
    return 0; 
} 


