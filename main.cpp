#include <iostream>
#include "Trie.hpp"

int main(){
	Trie trie;
	trie.insert("eprouve");
	trie.insert("emue");
    trie.insert("epee");
    trie.insert("epars");
    trie.insert("emule");

    trie.insert("epbr");
    trie.insert("emet");
    trie.insert("emis");
    trie.insert("emzgt");
    trie.insert("durum");
    trie.insert("pitta");
    trie.insert("ognon");
    trie.insert("andalouse");
    trie.insert("abracadabra");
    trie.insert("linh");
    trie.insert("epees");

    trie.search("linh");

    trie.printTrie();
    std::cout << "############################################################" << std::endl;
    trie.del("andalouse");
    trie.del("abracadabra");
    trie.del("epees");
    trie.del("emzgt");
    trie.del("epbr");






    trie.printTrie();
	return 0;
}