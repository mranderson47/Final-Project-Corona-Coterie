// Project1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <cstddef>
#include <queue>
#include <unordered_map>
#include <vector>
#include <math.h>

using namespace std;

struct Node
{

    string date;
    string province;
    string country;
    string confirmed;
    string deaths;
    string revovered;


};

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
        getline(fin, line);
        Node node;
        AVL AVLList;

        //For each line, make a new node
        while (!fin.eof())
        {
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

            //insert node into AVL
            AVLList.root = AVLList.insertAVLNode(AVLList.root, node);

        }

        cout << "Finished loading all data!" << endl;

        cout << "Search for: ";
        getline(cin, country);

        //search country in AVL
        unordered_map<string, vector<Node>> provList;
        AVLList.searchAVLNode(AVLList.root, country, provList);

        cout << endl;

        //MAKE ORDERED MAP
        //Print provinces
        for (unordered_map<string, vector<Node>>::const_iterator it = provList.begin(); it != provList.end(); it++) {
            cout << it->first << endl;
        }
        cout << "\nPick Province: ";

        //Print data

    }
    //If we were not able to open the file, exit the program.
    else
    {
        cout << "File cannot be opened! Please Try Again." << endl;
        return 0;
    }


}

