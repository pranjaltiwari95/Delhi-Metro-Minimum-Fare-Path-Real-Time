#include <bits/stdc++.h>
#include <iostream>
#include <fstream>
#include <string>
#include <queue>
using namespace std;



// Forward declarations
class MetroStop;
class MetroLine;
class AVLNode;

// MetroStop class
class MetroStop {
private:
    std::string stopName;
    MetroStop* nextStop;
    MetroStop* prevStop;
    MetroLine* line;
    int fare;

public:
    MetroStop(std::string name, MetroLine* metroLine, int fare);

    // Getter methods
    std::string getStopName() const;
    MetroStop* getNextStop() const;
    MetroStop* getPrevStop() const;
    MetroLine* getLine() const;
    int getFare() const;

    // Setter methods
    void setNextStop(MetroStop* next);
    void setPrevStop(MetroStop* prev);
};

MetroStop::MetroStop(std::string name, MetroLine* metroLine, int fare) {
    stopName = name;
    nextStop = nullptr;
    prevStop = nullptr;
    line = metroLine;
    this->fare = fare;
}

std::string MetroStop::getStopName() const {
    return stopName;
}

MetroStop* MetroStop::getNextStop() const {
    return nextStop;
}

MetroStop* MetroStop::getPrevStop() const {
    return prevStop;
}

MetroLine* MetroStop::getLine() const {
    return line;
}

int MetroStop::getFare() const {
    return fare;
}

void MetroStop::setNextStop(MetroStop* next) {
    nextStop = next;
}

void MetroStop::setPrevStop(MetroStop* prev) {
    prevStop = prev;
}

// MetroLine class
class MetroLine {
private:
    std::string lineName;
    MetroStop* node;

public:
    MetroLine(std::string name);

    // Getter methods
    std::string getLineName() const;
    MetroStop* getNode() const;

    // Setter methods
    void setNode(MetroStop* node);

    void populateLine(std::string filename);

    // helper function
    void printLine() const;
    int getTotalStops() const;
};

MetroLine::MetroLine(std::string name) {
    lineName = name;
    node = nullptr;
}

std::string MetroLine::getLineName() const {
    return lineName;
}

MetroStop* MetroLine::getNode() const {
    return node;
}

void MetroLine::setNode(MetroStop* node) {
    this->node = node;
}

void MetroLine::printLine() const {
    MetroStop* stop = node;
    while (stop != nullptr) {
        cout << stop->getStopName() << endl;
        stop = stop->getNextStop();
    }
}

int MetroLine::getTotalStops() const {
    int c = 0;
    MetroStop *stop = node;
    while (stop != nullptr)
    {
        c++;
        stop = stop->getNextStop();
    }
    return c ;

}

void MetroLine::populateLine(std::string filename) 
{ifstream fptr;
    fptr.open(filename);
    string line;
    int c = 0;
    while (getline(fptr, line))
    {
        string words[100];
        string name;
        stringstream word(line);
        int x = 0;
        int fair;
        while (word >> words[x])
        { fair = 0;
        x++;}
        name = words[0];
        fair = x-1;
        for (int j = 1; j < fair; j++)
        {
            name = name + ' ' + words[j];
        }
        int fare = stoi(words[fair]);
        if (c == 0)
        {fair = 0;
        setNode(new MetroStop(name, this, fare));
            c++;}
        else
        {
            MetroStop *stop = getNode();
            while (stop->getNextStop() != nullptr)
            { fair = 0;
                stop = stop->getNextStop();}
            stop->setNextStop(new MetroStop(name, this, fare));
            stop->getNextStop()->setPrevStop(stop);
        }
    }
    fptr.close();}

 
// AVLNode class
class AVLNode {
private:
    std::string stopName;
    std::vector<MetroStop*> stops;
    AVLNode* left;
    AVLNode* right;
    AVLNode* parent;

public:
    AVLNode(std::string name);

    // Getter methods
    std::string getStopName() const;
    const std::vector<MetroStop*>& getStops() const;
    AVLNode* getLeft() const;
    AVLNode* getRight() const;
    AVLNode* getParent() const;

    // Setter methods
    void addMetroStop(MetroStop* metroStop);
    void setLeft(AVLNode* left);
    void setRight(AVLNode* right);
    void setParent(AVLNode* parent);
};

AVLNode::AVLNode(std::string name) {
    stopName = name;
    left = nullptr;
    right = nullptr;
}

std::string AVLNode::getStopName() const {
    return stopName;
}

const std::vector<MetroStop*>& AVLNode::getStops() const {
    return stops;
}

AVLNode* AVLNode::getLeft() const {
    return left;
}

AVLNode* AVLNode::getRight() const {
    return right;
}

AVLNode* AVLNode::getParent() const {
    return parent;
}

void AVLNode::setLeft(AVLNode* left) {
    this->left = left;
}

void AVLNode::setRight(AVLNode* right) {
    this->right = right;
}

void AVLNode::setParent(AVLNode* parent) {
    this->parent = parent;
}

void AVLNode::addMetroStop(MetroStop* metroStop) {
    stops.push_back(metroStop);
}

// AVLTree class
class AVLTree {
    // Define your AVLTree implementation here.
private:
    AVLNode* root;

public:
    // getter methods
	//
	AVLTree(){
		root=nullptr;
	}
    AVLNode* getRoot() const;

    // setter methods
    void setRoot(AVLNode* root);

    // helper functions
    int height(AVLNode* node);
    int balanceFactor(AVLNode* node);
    AVLNode* rotateLeft(AVLNode* node);
    AVLNode* rotateRight(AVLNode* node);
    void balance(AVLNode* node);
    int stringCompare(string s1, string s2);
    AVLNode* insert(AVLNode* node, MetroStop* metroStop);
    void populateTree(MetroLine* metroLine);
    void inOrderTraversal(AVLNode* node);
    int getTotalNodes(AVLNode* node);
    AVLNode* searchStop(string stopName);
};

AVLNode* AVLTree::getRoot() const {
    return root;
}

void AVLTree::setRoot(AVLNode* root) {
    this->root = root;
}

int AVLTree::height(AVLNode* node) {
	if(node==NULL){
		return 0;
	}
	int lh = height(node->getLeft());
	int rh = height(node->getRight());
	return 1 + max(lh,rh);
}

int AVLTree::stringCompare(string s1, string s2) {
    return strcmp(s1.c_str(), s2.c_str());
}

int AVLTree::balanceFactor(AVLNode* node) {
	if(node==NULL){
		return 0;
	}
	return (height(node->getLeft()) - height(node->getRight()));
}

AVLNode* AVLTree::rotateLeft(AVLNode* node) {
	AVLNode*temp = node->getRight();
	AVLNode*temp2 = temp->getLeft();

	temp->setLeft(node);
	node->setRight(temp2);

	return temp;

}

AVLNode* AVLTree::rotateRight(AVLNode* node) {
	AVLNode*temp = node->getLeft();
	AVLNode* temp2 = temp->getRight();

	temp->setRight(node);
	node->setLeft(temp2);

	return temp;
}

void AVLTree::balance(AVLNode* node) {
}

AVLNode* AVLTree::insert(AVLNode* node, MetroStop* metroStop) {
	if(node==NULL){
		AVLNode* temp = new AVLNode(metroStop->getStopName());
		temp->addMetroStop(metroStop);
		return temp;
	}

	if(stringCompare(node->getStopName(), metroStop->getStopName()) > 0){
		node->setLeft(insert(node->getLeft(), metroStop));
	}else if(stringCompare(node->getStopName(), metroStop->getStopName())<0){
		node->setRight(insert(node->getRight(), metroStop));
	}else if(node->getStopName() == metroStop->getStopName()){
		node->addMetroStop(metroStop);
		return node;
	}

	int balancing = balanceFactor(node);

	if(balancing>1 && stringCompare(node->getLeft()->getStopName(), metroStop->getStopName()) >0){
		return rotateRight(node);
	}
	if(balancing<-1 && stringCompare(node->getRight()->getStopName(), metroStop->getStopName())< 0){
		return rotateLeft(node);
	}
	if(balancing>1 && stringCompare(node->getLeft()->getStopName(), metroStop->getStopName())<0){
		node->setLeft(rotateLeft(node->getLeft()));
		return rotateRight(node);
	}
	if(balancing<-1 && stringCompare(node->getRight()->getStopName(), metroStop->getStopName())>0){
		node->setRight(rotateRight(node->getRight()));
		return rotateLeft(node);
	}

	return node;
}

void AVLTree::populateTree(MetroLine* metroLine) {
	MetroStop*head = metroLine->getNode();
	vector<MetroStop*>ALLSTOPS;
	while(head!=NULL){
		ALLSTOPS.push_back(head);
		head=head->getNextStop();
	}
	for(auto x: ALLSTOPS){
		setRoot(insert(getRoot(),x));
	}
}

void AVLTree::inOrderTraversal(AVLNode* node) {
    if (node == nullptr) {
        return;
    }
    inOrderTraversal(node->getLeft());
    cout << node->getStopName() << endl;
    inOrderTraversal(node->getRight());
}

int AVLTree::getTotalNodes(AVLNode* node) {
    if (node == nullptr) {
        return 0;
    }
    return 1 + getTotalNodes(node->getLeft()) + getTotalNodes(node->getRight());
}

AVLNode* AVLTree::searchStop(string stopName) {
	AVLNode* traverse = getRoot();
	if(traverse==NULL){
		return traverse;
	}
	AVLNode *ans;
	while(traverse!=NULL){
		if(stringCompare(traverse->getStopName(), stopName)>0){
			traverse = traverse->getLeft();
		}else if(stringCompare(traverse->getStopName(), stopName)<0){
			traverse = traverse->getRight();
		}else{
			ans = traverse;
			break;
		}
	}
	return ans;

}

// Trip class
class Trip {
private:
    MetroStop* node;
    Trip* prev;

public:
    Trip(MetroStop* metroStop, Trip* previousTrip);

    // Getter methods
    MetroStop* getNode() const;
    Trip* getPrev() const;
};

Trip::Trip(MetroStop* metroStop, Trip* previousTrip) {
    node = metroStop;
    prev = previousTrip;
}

MetroStop* Trip::getNode() const {
    return node;
}

Trip* Trip::getPrev() const {
    return prev;
}

// Exploration class is a queue that stores unexplored Trip objects
class Exploration {
private:

    std::queue<Trip*> trips;

public:
    Exploration();

    // Getter methods
    std::queue<Trip*> getTrips() const;

    // Setter methods
    void enqueue(Trip* trip);
    Trip* dequeue();
    bool isEmpty() const;
};

Exploration::Exploration() {
}

std::queue<Trip*> Exploration::getTrips() const {
    return trips;
}

void Exploration::enqueue(Trip* trip) {
    trips.push(trip);
}

Trip* Exploration::dequeue() {
    if (trips.empty()) {
        return nullptr;
    }
    Trip* trip = trips.front();
    trips.pop();
    cout << "Dequeued: " << trip->getNode()->getStopName() << endl;
    return trip;
}

bool Exploration::isEmpty() const {
    return trips.empty();
}

class Path {
private:
    std::vector<MetroStop*> stops;
    int totalFare;

public:
    Path();

    // Getter methods
    std::vector<MetroStop*> getStops() const;
    int getTotalFare() const;

    // Setter methods
    void addStop(MetroStop* stop);
    void setTotalFare(int fare);

    // helper functions
    void printPath() const;
};

Path::Path() {
    totalFare = 0;
}

std::vector<MetroStop*> Path::getStops() const {
    return stops;
}

int Path::getTotalFare() const {
    return totalFare;
}

void Path::addStop(MetroStop* stop) {
    stops.push_back(stop);
}

void Path::setTotalFare(int fare) {
    totalFare = fare;
}

void Path::printPath() const {
    for (auto stop : stops) {
        cout << stop->getStopName() << endl;
    }
}

// PathFinder class
class PathFinder {
private:
    AVLTree* tree;
    std::vector<MetroLine*> lines;

public:
    PathFinder(AVLTree* avlTree, const std::vector<MetroLine*>& metroLines);
    void createAVLTree();
    Path* findPath(std::string origin, std::string destination);

    // Getter methods
    AVLTree* getTree() const;
    const std::vector<MetroLine*>& getLines() const;
};

PathFinder::PathFinder(AVLTree* avlTree, const std::vector<MetroLine*>& metroLines) {
    tree = avlTree;
    lines = metroLines;
}

AVLTree* PathFinder::getTree() const {
    return tree;
}

const std::vector<MetroLine*>& PathFinder::getLines() const {
    return lines;
}

void PathFinder::createAVLTree() {
    for (auto line:lines)
    {
        tree->populateTree(line);
    }
}

Path* PathFinder::findPath(std::string origin, std::string destination) {   
    // Distances map to store shortest distance (fare) to each station
    std::map<std::string, int> distances;
    
    // Previous stations map to reconstruct the shortest path
    std::map<std::string, std::string> prev_stations;
    
    // Priority queue to store stations based on their cumulative fare
    std::priority_queue<std::pair<int, std::string>, std::vector<std::pair<int, std::string>>, std::greater<std::pair<int, std::string>>> pq;
    
    // Initialization
    for (auto& line : lines) {
        MetroStop* stop = line->getNode();
        while (stop) {
            distances[stop->getStopName()] = INT_MAX;
            stop = stop->getNextStop();
        }
    }
    distances[origin] = 0;
    pq.push({0, origin});
    
    while (!pq.empty()) {
        int curr_fare = pq.top().first;
        std::string curr_station = pq.top().second;
        pq.pop();
        
        // If we reached the destination, break
        if (curr_station == destination) break;

        // Explore neighbors (i.e., next and previous stops)
        AVLNode* node = tree->searchStop(curr_station);
        for (auto& stop : node->getStops()) {
            if (stop->getNextStop() && distances[stop->getNextStop()->getStopName()] > curr_fare + abs( stop->getNextStop()->getFare()- stop->getFare())) {
                distances[stop->getNextStop()->getStopName()] = curr_fare + abs( stop->getNextStop()->getFare()- stop->getFare());
                prev_stations[stop->getNextStop()->getStopName()] = curr_station;
                pq.push({distances[stop->getNextStop()->getStopName()], stop->getNextStop()->getStopName()});
            }
            
            if (stop->getPrevStop() && distances[stop->getPrevStop()->getStopName()] > curr_fare + abs( stop->getPrevStop()->getFare()- stop->getFare())) {
                distances[stop->getPrevStop()->getStopName()] = curr_fare + abs( stop->getPrevStop()->getFare() - stop->getFare());
                prev_stations[stop->getPrevStop()->getStopName()] = curr_station;
                pq.push({distances[stop->getPrevStop()->getStopName()], stop->getPrevStop()->getStopName()});
            }
        }
    }
    
    // Reconstruct the path
    Path* path = new Path();
    std::string station = destination;
    while (station != origin) {
        path->addStop(tree->searchStop(station)->getStops()[0]);  // Adding the first stop with the given name
        station = prev_stations[station];
    }
    path->addStop(tree->searchStop(origin)->getStops()[0]);  // Adding the origin station
    path->setTotalFare(distances[destination]);
    return path;
}
    
vector<MetroLine*> lines;