
#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <fstream>
#include <cstddef>
#include <queue>
#include <unordered_map>
#include <vector>
#include <map>
#include <math.h>
#include <chrono>

using namespace std;

//Node structure for map data structure
struct Node
{
    //We want to store each node in a tree/map as an ADT

    //Tags associated with the data
    string date;
    string province;
    string country;

    //The contents of the data
    string confirmed;
    string deaths;
    string revovered;

    //Any duplicate countries should be stored in here since we cannot have duplicate keys
    vector<Node> dupes;

};

//AVL structure class
class AVL {
public:
    //Initialize AVLNode
    class AVLNode {
    public:
        string Country = "";
        int height = NULL;
        AVLNode* left = NULL;
        AVLNode* right = NULL;
        unordered_map<string, vector<Node>> AVLmap;
    }*root;

    AVL();
    AVLNode* rotateLeft(AVLNode* root);
    AVLNode* rotateRight(AVLNode* root);
    AVLNode* rotateLeftRight(AVLNode* root);
    AVLNode* rotateRightLeft(AVLNode* root);
    int heightAVLNode(AVLNode*);
    int balanceFactor(AVLNode* root);
    AVLNode* balanceAVLNode(AVLNode* root);
    AVLNode* insertAVLNode(AVLNode* root, Node data);
    void searchAVLNode(AVLNode* root, string country, unordered_map<string, vector<Node>>& list);
};

//Initialize AVL Tree
AVL::AVL() {
    root = NULL;
}

//All rotate methods are from my code from Stepik 5.1.1 and 5.1.3
AVL::AVLNode* AVL::rotateLeft(AVLNode* root) {    //O(1)
    AVLNode* gC = root->right->left;   //grandchild
    AVLNode* nP = root->right;   //new parent
    nP->left = root;    //swap
    root->right = gC;    //swap
    //adjust height
    int maxHeight = (heightAVLNode(root->left) > heightAVLNode(root->right)) ? heightAVLNode(root->left) : heightAVLNode(root->right);
    root->height = maxHeight + 1;
    maxHeight = (heightAVLNode(nP->left) > heightAVLNode(nP->right)) ? heightAVLNode(nP->left) : heightAVLNode(nP->right);
    nP->height = maxHeight + 1;
    return nP;
}

AVL::AVLNode* AVL::rotateRight(AVLNode* root) {    //O(1)
    AVLNode* gC = root->left->right;   //grandchild
    AVLNode* nP = root->left;   //new parent
    nP->right = root;   //swap
    root->left = gC;   //swap
    //adjust height
    int maxHeight = (heightAVLNode(root->left) > heightAVLNode(root->right)) ? heightAVLNode(root->left) : heightAVLNode(root->right);
    root->height = maxHeight + 1;
    maxHeight = (heightAVLNode(nP->left) > heightAVLNode(nP->right)) ? heightAVLNode(nP->left) : heightAVLNode(nP->right);
    nP->height = maxHeight + 1;
    return nP;
}

AVL::AVLNode* AVL::rotateLeftRight(AVLNode* root) {    //O(1)
    AVLNode* L = root->left;
    L = rotateLeft(L);   //rotate left
    root->left = L;
    AVLNode* newN = rotateRight(root);   //rotate right
    return newN;
}

AVL::AVLNode* AVL::rotateRightLeft(AVLNode* root) {    //O(1)
    AVLNode* R = root->right;
    R = rotateRight(R);    //rotate right
    root->right = R;
    AVLNode* newN = rotateLeft(root);   //rotate left
    return newN;
}

int AVL::heightAVLNode(AVLNode* root) {    //O(1)
    if (root == nullptr)    //empty, return height as 0
        return 0;
    else          //else return height
        return root->height;
}

int AVL::balanceFactor(AVLNode* root) {        //O(1)
    if (root == NULL)   //check if empty
        return 0;
    else    //else get bF
        return heightAVLNode(root->left) - heightAVLNode(root->right);
}

AVL::AVLNode* AVL::balanceAVLNode(AVLNode* root) {    //O(1)
    //find balance factors
    int bF = balanceFactor(root);
    int bFL = balanceFactor(root->left);
    int bFR = balanceFactor(root->right);
    if (bF > 1) {   //child to the left
        if (bFL > 0)    //grandchild to the left
            root = rotateRight(root);
        else     //grandchild to the right
            root = rotateLeftRight(root);
    }
    else if (bF < -1) { //child to the right
        if (bFR < 0)    //grandchild to the right
            root = rotateLeft(root);
        else     //grandchild to the left
            root = rotateRightLeft(root);
    }
    return root;
}

//Reference code from Stepik 4.3.1
AVL::AVLNode* AVL::insertAVLNode(AVLNode* root, Node data) {       //O(logn)
    if (root == NULL) {     //check if empty, just add new AVLNode
        root = new AVLNode;
        root->Country = data.country;
        root->left = NULL;
        root->right = NULL;
        root->height = 1;
        root->AVLmap[data.province].push_back(data);
        return root;
    }
    else if (root->Country.compare(data.country) < 0)  //if less than current root's country, go left
        root->left = insertAVLNode(root->left, data);
    else if (root->Country.compare(data.country) > 0)  //if greater than current root's country, go right
        root->right = insertAVLNode(root->right, data);
    else if (root->Country.compare(data.country) == 0) {   //if already has that country, push_back into map's vector
        root->AVLmap[data.province].push_back(data);
        return root;
    }
    int maxHeight = (heightAVLNode(root->left) > heightAVLNode(root->right)) ? heightAVLNode(root->left) : heightAVLNode(root->right);
    root->height = maxHeight + 1;    //adjust the height
    return balanceAVLNode(root);   //rebalance
}

//Stepik 4.3.3 find Node
void AVL::searchAVLNode(AVLNode* root, string country, unordered_map<string, vector<Node>>& list) {     //O(logn)
    if (root == NULL) {     //check if empty
        cout << "Not found" << endl;
    }
    else if (root->Country.compare(country) < 0)  //if less than current root's country, go left
        searchAVLNode(root->left, country, list);
    else if (root->Country.compare(country) > 0)  //if greater than current root's country, go right
        searchAVLNode(root->right, country, list);
    else if (root->Country.compare(country) == 0)   //found country, save map
        list = root->AVLmap;

    return;
}

int main()
{
    cout << "Welcome to the Corona Coterie Data Index!" << endl;

    

    //Load our file stream.
    fstream fin;
    string file = "data.csv";

    //Open the data to be parsed.
    fin.open(file);

    //***********PARSING************//

    //Determine if we successfully opened the file.
    if (fin.is_open())
    {
        int index;
        string line;
        string country;
        string province;
        getline(fin, line);
        
        AVL AVLList;
        //Init our map container to store nodes
        map<string, Node> mp;


       



        //For each line, make a new node
        //Insertion into AVL, separate loop for insertion comparisons
        auto start = chrono::high_resolution_clock::now();
        while (!fin.eof())
        {
            Node node;
            getline(fin, line);
            //Start our index
            index = line.find(",");

            //Store the date for each node
            node.date = line.substr(index + 1, line.find(",", index + 1) - index - 1);

            //Update the index
            index = line.find(",", index + 1);

            //Store the province for each node
            node.province = line.substr(index + 1, line.find(",", index + 1) - index - 1);

            //Update the index
            index = line.find(",", index + 1);

            //Store the country for each node
            node.country = line.substr(index + 1, line.find(",", index + 1) - index - 1);

            //Update the index
            index = line.find(",", index + 1);

            //Store the confirmed number of cases
            node.confirmed = line.substr(index + 1, line.find(",", index + 1) - index - 1);

            //Update the index
            index = line.find(",", index + 1);

            //Store the  number of deaths
            node.deaths = line.substr(index + 1, line.find(",", index + 1) - index - 1);

            //Update the index
            index = line.find(",", index + 1);

            //Store the  number of recovered
            node.revovered = line.substr(index + 1, line.find(",", index + 1) - index - 1);

            //Update the index
            index = line.find(",", index + 1);


            //*****Test printing data to make sure it is accurate*********//

            //cout << node.date << " " << node.province << " " << node.country << " " << node.confirmed << " " << node.deaths << " " << node.revovered << endl;


            //******INSERTION INTO DATA STRUCTURES******//

            
            AVLList.root = AVLList.insertAVLNode(AVLList.root, node);
            
        }
        auto finish = chrono::high_resolution_clock::now();

       
        cout << "It took the AVL " << (finish - start).count() << " nanoseconds" << " for an average of " << ((finish - start).count() / 116805) << " microseconds per node!" << endl;
        //Insertion into a map, separate loop for insertion comparisons
        
        auto start2 = chrono::high_resolution_clock::now();
        while (!fin.eof())
        {
            Node node;
            getline(fin, line);
            //Start our index
            index = line.find(",");

            //Store the date for each node
            node.date = line.substr(index + 1, line.find(",", index + 1) - index - 1);

            //Update the index
            index = line.find(",", index + 1);

            //Store the province for each node
            node.province = line.substr(index + 1, line.find(",", index + 1) - index - 1);

            //Update the index
            index = line.find(",", index + 1);

            //Store the country for each node
            node.country = line.substr(index + 1, line.find(",", index + 1) - index - 1);

            //Update the index
            index = line.find(",", index + 1);

            //Store the confirmed number of cases
            node.confirmed = line.substr(index + 1, line.find(",", index + 1) - index - 1);

            //Update the index
            index = line.find(",", index + 1);

            //Store the  number of deaths
            node.deaths = line.substr(index + 1, line.find(",", index + 1) - index - 1);

            //Update the index
            index = line.find(",", index + 1);

            //Store the  number of recovered
            node.revovered = line.substr(index + 1, line.find(",", index + 1) - index - 1);

            //Update the index
            index = line.find(",", index + 1);

            //*****Test printing data to make sure it is accurate*********//

            //cout << node.date << " " << node.province << " " << node.country << " " << node.confirmed << " " << node.deaths << " " << node.revovered << endl;


            //******INSERTION INTO DATA STRUCTURES******//

            //insert node into map
            //first find if there is a duplicate country data
            //if so, we need to store it on the node's vector instead
            //if no dupes, then we can simply add the node to the map

         

            
            //find if our country is already in the map using iterator
            auto found = mp.find(node.country);

            //If not found, add to the map
            if (found == mp.end())
            {
                cout << "ADDED" << endl;
                mp.emplace(node.country, node);
            }
            //If it already exists, insert it into the duplicates vector of the node
            else
            {
                cout << "DUPE" << endl;
                found->second.dupes.push_back(node);
            }
        }
        auto finish2 = chrono::high_resolution_clock::now();

        
        cout << "It took the MAP " << (finish2 - start2).count() << " nanoseconds" << " for an average of " << ((finish2 - start2).count() / 116805) << " microseconds per node!" << endl;
        cout << "Finished loading all data!" << endl;



        while (true)
        {

            cout << "Search a country to see all available provinces, or type quit to exit: ";
            getline(cin, country);

            if (country == "quit")
            {
                return 0;
            }

            //search country in AVL
            unordered_map<string, vector<Node>> provList;
            map<string, vector<Node>> orderedProvList;
            AVLList.searchAVLNode(AVLList.root, country, provList);

            cout << endl;

            //MAKE ORDERED MAP
            //Print provinces
            for (unordered_map<string, vector<Node>>::const_iterator it = provList.begin(); it != provList.end(); it++) {
                //cout << it->first << endl;
                orderedProvList[it->first] = it->second;
            }

            for (auto it = orderedProvList.begin(); it != orderedProvList.end(); it++) {
                if (it->first != "")
                    cout << it->first << endl;
            }

            cout << "\nPick a province to view all related Coronavirus statistics, or type quit to exit: " << endl;
            
            getline(cin, province);

            if (province == "quit")
            {
                cout << "Thank you for using the Corona Coterie database, goodbye!" << endl;
                return 0;
            }

            //Print data
            cout << "Date:" << setw(20) << "Province" << setw(15) << "Country" << setw(15) << "Confirmed" << setw(15) << "Deaths" << setw(15) << "Recovered" << endl;
            for (int i = 0; i < provList[province].size(); i++) {

                cout << setw(17) << left << provList[province].at(i).date << setw(16) << provList[province].at(i).province << setw(13) << provList[province].at(i).country << setw(18)
                    << provList[province].at(i).confirmed << setw(13) << provList[province].at(i).deaths << setw(9) << provList[province].at(i).revovered << endl;

            }

        }
    }
    //If we were not able to open the file, exit the program.
    else
    {
        cout << "File cannot be opened! Please Try Again." << endl;
        return 0;
    }


}

