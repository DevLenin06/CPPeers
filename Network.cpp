# include <iostream>
# include <fstream>
# include <sstream>
# include <stdexcept>
# include "Network.h"

using std::string, std::vector;

Network::Network() : users({}), posts({}), tags({}) {}

void Network::loadFromFile(string fileName) {
    // TODO: load user and post information from file
    std::ifstream inFS(fileName);

    if(!inFS.is_open()) {
        throw std::invalid_argument("Could not open file");
    }

    try {

        string postLine;

        //keep reading until end of file
        while (getline(inFS, postLine)){
            //read beggining word to check for post and user
            std::istringstream iss(postLine);
            string indicatorWord;
            iss >> indicatorWord;

            if(indicatorWord == "User") {
                //next word will be the userName
                string userName;
                iss >> userName;
                if (userName == "") {
                    throw std::runtime_error("Invalid user format");
                }else if (iss.fail()) {
                    throw std::runtime_error("Invalid user format");
                }
                addUser(userName);
            }else if (indicatorWord == "Post") {
                int postId;
                string userName;
                string postText;

                //enter postId
                iss >> postId;
                // if (!isdigit(postId)){
                //     throw std::runtime_error("Invalid post format");
                // }
                if (iss.fail()) {
                    throw std::runtime_error("Invalid post format");
                }

                //enter username
                iss >> userName;
                if (iss.fail()) {
                    throw std::runtime_error("Invalid post format");
                }
                if (userName == ""){
                    throw std::runtime_error("Invalid post format");
                }
                //post text is a line
                getline(iss, postText );
                postText = postText.erase(0,1);
                //there is no post text
                if (postText == "") {
                    throw std::runtime_error("Invalid post format");
                }
                addPost(postId, userName, postText);
            }else {
                //invalid formation
                throw std::runtime_error("Invalid post format");
            }
        }
    }catch (std::invalid_argument& e) {
        throw std::runtime_error(" ");
    }
    
    inFS.close();
}

void Network::addUser(string userName) {
    // TODO: create user and add it to network

    //loop through and make it lowercase
    for (char& i : userName) {
        i = tolower(i);
    }


    string existingName;

    //check is there is a user that already has this name, make it lowercase and then compare
    //i point to the adress of the diff user
    for (User *CurrentUser: users) {
        existingName = CurrentUser-> getUserName();
        for (char& c: existingName){
            c = tolower(c);
        }

        if (existingName == userName) {
            throw std::invalid_argument("User already exists");
        }
    }

    //creat a new user
    User* addedUser = new User(userName);

    //add it to the list of users
    users.push_back(addedUser);



    //out put the added user
    std::cout << "Added User " << userName << std::endl;

    

}

void Network::addPost(unsigned int postId, string userName, string postText) {
    // TODO: create post and add it to network

    //look through posts to see if a post with the ID exists
    for (Post* existingPost : posts) {
        //check if it exists 
        if (existingPost -> getPostId() == postId ) {
            throw std::invalid_argument("Post already exists");
        } 
    }

    //debug thoughts, make username and exiting user lowercase
    


    
    //Find the user then, use it to see if no user exists
    User *user = nullptr;
    for (User *existingUser : users ) {
        // string existingName = existingUser->getUserName();
        // std::cout << "Debug: existingName" << existingUser->getUserName() << std::endl;
        // std::cout << "Debug: userName " << userName << std::endl;

        if (existingUser->getUserName() == userName ) {
            user = existingUser;
        }
    }

    //if nothing is assigned it doesn't exist
    if ( user == nullptr) {
        throw std::invalid_argument("User doesn't exist");
    }

    //create a new post
    Post* newPost = new Post(postId, userName, postText);


    //add to network data member posts
    posts.push_back(newPost);

    //addpost to the user
    user -> addUserPost(newPost);

    //extract hashtags from Post using the findTags() function, that function returns a vector
    vector<string> extractedTags = newPost -> findTags();
    //reading through actual tags, not just looking at memory
    for (string tag: extractedTags) {
        //search for the tag

        Tag *tagPointer = nullptr;

        //look through tags to find if they exist, and set memory location of Tagpointer
        for (Tag *currentTag : tags) {
            //check if it is equal to the tag we are currently at in the vector
            if (currentTag->getTagName() == tag){
                tagPointer = currentTag;
                break; //it exists
            }
        }

        //if it doesn't exist
        if (tagPointer == nullptr) {
            try {
                //tag is the string it is currently at at the vector extracted Tags
                tagPointer = new Tag(tag);
                //added to the list of tags
                tags.push_back(tagPointer);
            }catch (std::invalid_argument& e){
                continue;
            }
        }

        tagPointer-> addTagPost(newPost);
    }

    std::cout << "Added Post " << postId << " by " << userName << std::endl;



}

vector<Post*> Network::getPostsByUser(string userName) {
    // TODO: return posts created by the given user

    //userCheck is the point for the specified user

    User* userCheck = nullptr;
    for (User* existingName : users) {
        //check if the userName already exists
        if (existingName -> getUserName() == userName) {
            userCheck = existingName;
            break; //only need to find that one user
        }
    }

    if (userName == "") {
        throw std::invalid_argument("Empty Username");
    }
    //not found
    if(userCheck == nullptr) {
        throw std::invalid_argument("Username not found");
    }

    return userCheck -> getUserPosts();

}

vector<Post*> Network::getPostsWithTag(string tagName) {
    // TODO: return posts containing the given tag

    Tag* tagCheck = nullptr;
    for (Tag* existingTag: tags) {
        if (existingTag  -> getTagName() == tagName) {
            tagCheck = existingTag;
            break; //only need that one tag
        }
    }

    if (tagName == "") {
        throw std::invalid_argument("tagname is empty");
    }

    //it is still nullptr if tag is not found
    if (tagCheck == nullptr) {
        throw std::invalid_argument("tagName was not found");
    }

    
    return tagCheck -> getTagPosts();


    
}

vector<string> Network::getMostPopularHashtag() {
    // TODO: return the tag occurring in most posts

    //iterate through the tags
    int maxCount = 0;
    int postCount =0;
    string tagName;
    vector<string> Maxtags;
    for (Tag* tags: tags){
        tagName = tags->getTagName();
        postCount = getPostsWithTag(tagName).size();

        //if it is greater than max count it becomes the new maxCount
        if (postCount > maxCount) {
            maxCount = postCount;

            //add it to vector
            Maxtags = {tagName};

        }else if (postCount == maxCount) {
            Maxtags.push_back(tagName);
        }

    }
        
    return Maxtags;

    

    
}

Network::~Network() {
    for (unsigned int i = 0; i < users.size(); ++i) {
        delete users.at(i);
    }

    for (unsigned int i = 0; i < tags.size(); ++i) {
        delete tags.at(i);
    }
    
    for (unsigned int i = 0; i < posts.size(); ++i) {
        delete posts.at(i);
    }
}
