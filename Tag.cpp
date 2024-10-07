# include <string>
# include <stdexcept>
# include "Tag.h"

using std::string, std::vector;

Tag::Tag(string _tagName) : tagName(), tagPosts() {
    // TODO: implement constructor checks
    if (_tagName.size() < 2 || _tagName[0] != '#' || !isalpha(_tagName[1])) {
       throw std::invalid_argument(" ");
    }

    // check uppercase
    unsigned int i; 
    for (i = 0; i < _tagName.size(); i++ ) {
        if (isupper(_tagName[i])) {
            throw std::invalid_argument("Has uppercase letter");
        }
    }

    int j;
    for (j = _tagName.size() - 1; j >= 0; j --) {
        if (_tagName[j] == '!' || _tagName[j] == '?' || _tagName[j] == ',' || _tagName[j] == '.' ) {
            throw std::invalid_argument("");
        }
    }

    tagName = _tagName;
}

string Tag::getTagName() {
    // TODO: implement getter
    return tagName;
}

vector<Post*>& Tag::getTagPosts() {
    // TODO: implement getter
    return tagPosts;
}

void Tag::addTagPost(Post* post) {
    // TODO: add post to tag posts
    if (post == nullptr) {
        throw std::invalid_argument ("");
    }

    tagPosts.push_back(post);
}
