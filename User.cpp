# include <string>
# include <stdexcept>
# include "User.h"

using std::string, std::vector;

User::User(string _userName) : userName(), userPosts()  /* TODO: initialize */ {
    // TODO: implement constructor checks
    if (_userName == "") {
        throw std::invalid_argument(" ");

    }
    int i = 0;
    if (!isalpha(_userName[i])){
        throw std::invalid_argument(" ");
    }

    unsigned int j = 0;
    for (j = 0; j < _userName.size(); j++) {
        if (isupper(_userName[j])) {
            throw std::invalid_argument(" ");
        }
    }
    userName = _userName;
}

string User::getUserName() {
    // TODO: implement getter
    return userName;
}

vector<Post*>& User::getUserPosts() {
    // TODO: implement getter
    return userPosts;
}

void User::addUserPost(Post* post) {
    // TODO: add post to user posts
    if (post == nullptr) {
        throw std::invalid_argument(" ");
    }

    //added to user posts
    userPosts.push_back(post);
}
