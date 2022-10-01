#include <string>
#include "../trie/Node.h"

/**
 * @file Trie.h
 * @author Original JAVA by William Fiset (william.alexandre.fiset@gmail.com)
 *         C++ conversion by 0xChristopher
 * @brief Trie data structure implementation. This data structure provides a way to look up values of nodes
 *        which are stored in maps in parent nodes. For this reason, the root of the Trie is set to an
 *        arbitrary value. Each node is marked with a boolean that determines whether or not the node value
 *        marks the end of a word, as well as how many words the current node belongs to. This allows the
 *        data structure to know when to remove certain nodes. The Trie is great for applications such as 
 *        auto-complete functionality.
 * 
 *        Time Complexity: 
 *              Operation       Average     Best
 *              Insertion       O(n)        O(n)
 *              Deletion        O(n)        O(n)
 *              Search          O(n)        O(1)
 */

class Trie {

    private:
        const char rootCharacter = '.';         /// Root value (arbitrary)
        Node* root = new Node(rootCharacter);   /// Root node of Trie

        /**
         * @brief The Insert() function attempts to insert a string of characters into the Trie.
         * @param key The string to be inserted (key value in the map)
         * @param numInserts Number of insertions
         * @return Returns true upon successful insertion
         */
        bool Insert(std::string& key, int numInserts) {
            if (key.empty())
                throw "Empty string";
            else if (numInserts <= 0)
                throw "numInserts must be greater than zero";

            Node* node = root;
            bool createdNewNode = false;
            bool isPrefix = false;

            /// Process individual characters
            for (int i = 0; i < key.length(); i++) {
                char ch = key[i];
                Node* nextNode = node->children.at(ch);

                /// The next character doesn't exist
                if (nextNode == nullptr) {
                    nextNode = new Node(ch);
                    node->AddChild(nextNode, ch);
                    createdNewNode = true;

                /// The next character exists
                } else if (nextNode->isWordEnding) {
                    isPrefix = true;
                }

                node = nextNode;
                node->count += numInserts;
            }

            /// Root node cannot be word ending
            if (node != root)
                node->isWordEnding = true;

            return isPrefix || !createdNewNode;
        }

        /**
         * @brief The Remove() function attempts to remove a string from the Trie.
         * @param key The string to be removed
         * @param numDeletions Number of deletions
         * @return Returns true upon successful removal
         */
        bool Remove(std::string& key, int numDeletions) {
            if (!Contains(key))
                return false;

            Node* node = root;

            for (int i = 0; i < key.length(); i++) {
                char ch = key[i];
                Node* currentNode = node->children.at(ch);
                currentNode->count -= numDeletions;

                /// Cut this edge if the current node has a count <= 0
                /// This means that all the prefixes below this point are inaccessible
                if (currentNode->count <= 0) {
                    /// Free memory of soon to be inaccessible child nodes
                    for (std::map<char, Node*>::iterator it = currentNode->children.begin(); 
                        it != currentNode->children.end(); ++it) {
                        Clear(it->second);
                    }

                    delete currentNode;

                    /// Reset the child for future entries
                    node->RemoveChild(ch);

                    return true;
                }

                node = currentNode;
            }

            return true;
        }

        /**
         * @brief The Count() function gets the count value of a node based on the prefix (key)
         * @param key The string to check the count of
         * @return Returns the count of the prefix
         */
        int Count(std::string& key) {
            if (key.empty())
                throw "Empty string";

            Node* node = root;

            /// Dig into the Trie until we reach the bottom or our key doesn't exist
            for (int i = 0; i < key.length(); i++){
                char ch = key[i];

                if (node == nullptr)
                    return 0;

                node = node->children.at(ch);
            }

            if (node != nullptr)
                return node->count;

            return 0;
        }

        /// @brief The Clear() function clears all nodes and resets the Trie.
        /// @param node The root node to clear from
        void Clear(Node*& root) {
            if (root == nullptr)
                return;

            for (std::map<char, Node*>::iterator it = root->children.begin(); 
                it != root->children.end(); ++it) {
                if (it->second != nullptr) {
                    Clear(it->second);

                    char ch = it->first;

                    delete it->second;

                    /// Reset the child for future entries
                    root->RemoveChild(ch);
                }
            }
        }

    public:
        /// @brief Trie constructor and destructor
        Trie() {}

        ~Trie() {
            Clear(root);
            delete root;
        }

        /**
         * @brief The public facing Insert() function
         * @param key The key to be inserted
         * @return Returns true upon successful insertion
         */ 
        bool Insert(std::string& key) {
            return Insert(key, 1);
        }

        /**
         * @brief The public facing Remove() function
         * @param key The string to be removed
         * @return Returns true upon successful removal
         */
        bool Remove(std::string& key) {
            return Remove(key, 1);
        }

        /**
         * @brief The Contains() function checks if a string (key) is contained within the Trie.
         * @param key The string to be checked
         * @return Returns true if the string (key) is contained within the Trie
         */
        bool Contains(std::string& key) {
            return Count(key) != 0;
        }

        /// @brief The public facing Clear() function
        void Clear() {
            Clear(root);
        }

};