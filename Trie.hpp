#ifndef _TRIE_HPP
#define _TRIE_HPP

#include <cstddef>   // NULL, ptrdiff_t, size_t
//#include <stdecharcept> // exception types
#include <vector>  // dynamique liste.
#include <string>
#include <iostream>
#include <vector>

class Trie {

private:
    class _Noeud{
    public:
        inline _Noeud *get_first_child();
        inline _Noeud *get_brother();
        inline _Noeud *get_last_child();
        inline _Noeud *get_father();
        inline char get_name();
        inline bool get_bool();
        inline void set_bool(bool);
        inline void set_brother(_Noeud*);
        inline void set_first_child(_Noeud*);
        inline void set_father();

        _Noeud(char, _Noeud*, bool);
        _Noeud();
       //_Noeud( const _Noeud &tmp);
       // ~_Noeud();

    private:
        const char _name;
        _Noeud *_first_child;
        _Noeud *_brother;
        _Noeud *_father;
        bool _endOfWord;
    };
    _Noeud *_root;
    _Noeud *tmp; //utilisé pour avoir le dernier noeud quand on fait une recherche d'un mot

public:
    Trie(){createRoot();}
    inline std::vector<char> get_path();
    void insert(std::string);
    void createRoot();
    void printTrie(_Noeud* current, std::string);
    void del(std::string);
    bool search(std::string, _Noeud*, int);
    //~Trie();

};


// getter
Trie::_Noeud* Trie::_Noeud::get_brother(){
    return _brother;
}

Trie::_Noeud* Trie::_Noeud::get_first_child(){
    return _first_child;
}

char Trie::_Noeud::get_name(){
    return _name;
}

Trie::_Noeud* Trie::_Noeud::get_father(){
    return _father;
}
bool Trie::_Noeud::get_bool(){
    return _endOfWord;
}



// setter
void Trie::_Noeud::set_brother(_Noeud* brother){
    _brother = brother;
}

void Trie::_Noeud::set_bool(bool endOfWord){
    _endOfWord = endOfWord;
}

void Trie::_Noeud::set_first_child(_Noeud* first_child){
    _first_child = first_child;

}

void Trie::_Noeud::set_father() {
    _father = nullptr;
}


// méthode de Trie
void Trie::createRoot(){
    _root = new _Noeud();
}

bool Trie::search(std::string word, _Noeud* current = nullptr, int index = 0){
    bool found = false;
    if(!current)
        current=_root;

    if(current->get_first_child() && index < word.size())
    {
        current = current->get_first_child();
        if (word[index] == current->get_name()) {
            if(index == word.size()-1) {
                if (current->get_bool()){
                    found = true;
                    tmp = current;}
                else
                    return false;
            }

            else
                found = search(word, current, index + 1);
        }

        while (current->get_brother() && current->get_brother()->get_name() <= word[index] && !found){
            if (word[index] == current->get_name()) {
                if (index == word.size() - 1){
                    if(current->get_bool()){
                        found = true;
                        tmp = current;
                    }
                    else
                        return false;
                }

                else{
                    found = search(word, current, index + 1);
                    current = current->get_brother();
                }
            }

            else{
                current = current->get_brother();
                if(!current->get_brother() && word[index] == current->get_name() &&
                index == word.size()-1 && current->get_bool() ){
                    found = true;
                    tmp = current;}
                else
                    found = search(word, current, index + 1);
                }

            }

        }
    return found;
}


void Trie::insert(std::string word){

    size_t size = word.size();
    _Noeud* current = _root;
    char letter;
    bool end = false, same_char, insert_place_1st, insert_place;
    for(size_t i = 0; i<size; i++){
        if(i==size-1)
            end = true;
        letter = word[i];
        same_char = false , insert_place = false, insert_place_1st =false;
        // si le noeud à un fils, on va check si y en pas un qui existe déjà pour la lettre courrante
        if(current->get_first_child()) {
            current = current->get_first_child();

            if (current->get_name() == letter)
                same_char = true;
            else if(current->get_name() > letter)
                insert_place_1st = true;
            else if(!(current->get_brother()))
                insert_place = true;

            while (current->get_brother() && !same_char && !insert_place) {

                if (current->get_name() == letter)
                    same_char = true;
                else if (current->get_brother()->get_name() > letter )
                    insert_place = true;
                else{
                    current = current->get_brother();
                    if(!(current->get_brother()) && current->get_name()==letter)
                        same_char=true;
                    else if(!(current->get_brother()))
                        insert_place =true;
                }
            }

            if (insert_place_1st){
                _Noeud* tmp = current;
                current = new _Noeud(letter, current->get_father(), end);
                current->set_brother(tmp);
                tmp->get_father()->set_first_child(current);

            }

            else if (insert_place){
                _Noeud* tmp = current;
                current = new _Noeud(letter, current->get_father(), end);
                current->set_brother(tmp->get_brother());
                tmp->set_brother(current);
            }

            else if(same_char && i == size - 1)
                current->set_bool(true);
        }

        // pas de fils
        else{
            _Noeud* tmp = current;
            current = new _Noeud(letter, current, end);
            tmp->set_first_child(current);
        }
    }
}

void Trie::del(std::string word){
    if(search(word)) {

        if(tmp->get_first_child()){
            tmp->set_bool(false);
        }
        else {
            while (tmp->get_father() && !(tmp->get_father()->get_bool())) {
                tmp = tmp->get_father();
                if (tmp->get_brother() || tmp->get_father()->get_first_child() != tmp)
                    break;
            }

            //pour avoir le précédent du noeud qu'on doit delete
            _Noeud *previous = tmp->get_father()->get_first_child();
            if (previous == tmp) {
                if (tmp->get_brother()) {
                    tmp->get_father()->set_first_child(tmp->get_brother());
                    delete tmp;
                } else {
                    tmp->get_father()->set_first_child(nullptr);
                    delete tmp;
                }
            } else {

                while (previous->get_brother() != tmp) {
                    previous = previous->get_brother();
                }
                if(tmp->get_brother())
                    previous->set_brother(tmp->get_brother());
                else
                    previous->set_brother(nullptr);
                tmp->set_father();
                delete tmp;
            }
        }
    }
}

void Trie::printTrie(_Noeud* current = nullptr, std::string word = "") {
    if(!current)
        current=_root;
    if(current->get_bool())
        std::cout << word << std::endl;
    if(current->get_first_child())
        printTrie(current->get_first_child(), word + current->get_first_child()->get_name());
    if(current->get_brother()) {
        word.pop_back();
        printTrie(current->get_brother(), word+current->get_brother()->get_name());
    }
}

// constructeur
Trie::_Noeud::_Noeud(char name, _Noeud* father, bool endOfWord):
        _name(name), _first_child(nullptr), _brother(nullptr), _father(father),
        _endOfWord(endOfWord){}



// constructeur de la racine
Trie::_Noeud::_Noeud():
        _name(' '), _first_child(nullptr), _brother(nullptr), _endOfWord(0){}


//constructeur de copie
/*Trie::_Noeud::_Noeud(const _Noeud &tmp) {
    _Noeud * x = new _Noeud(tmp.get_name(), tmp.get_father(), tmp.get_bool())
}*/

// fonction supplémentaire
Trie::_Noeud* Trie::_Noeud::get_last_child(){
    _Noeud* current = this->get_first_child();

    if(current) {
        _Noeud *next = current->get_brother();
        if(next){
            while (next->get_brother()) {
                current = next;
                next = next->get_brother();}

            return next;
        }
    }
    return current;
}


#endif /* _TRIE_HPP */