# include <iostream>
# include <string>
# include <stdexcept>
# include "Post.h"

using std::string, std::vector;

Post::Post(unsigned int postId, string userName, string postText) : postId(postId), userName(userName), postText(postText) {
    if (postId == 0 || userName == "" || postText == "") {
        throw std::invalid_argument("post constructor: invalid parameter values");
    }
}

unsigned int Post::getPostId() {
    return postId;
}

string Post::getPostUser() {
    return userName;
}

string Post::getPostText() {
    return postText;
}

vector<string> Post::findTags() {
    std::vector<std::string> foundTags;

    std::string newWord = "";
    

    for (char character : postText) {
        if (character == ' ' || character == ',' || character == '!' || character == '?' || character == '.') {
            if (!newWord.empty() && newWord[0] == '#') {
                for (size_t i = 1; i < newWord.size(); i++) {
                    newWord[i] = tolower(newWord[i]);
                }
                foundTags.push_back(newWord);
            }
            // Reset newWord for the next word
            newWord = "";
        } else {
            // Append the current character to newWord
            newWord += character;
        }
    }

    if (!newWord.empty() && newWord[0] == '#') {
        for (size_t i = 1; i < newWord.size(); i++) {
            newWord[i] = tolower(newWord[i]);
        }
        foundTags.push_back(newWord);
    }

    

    return foundTags;
    
    
    


}
