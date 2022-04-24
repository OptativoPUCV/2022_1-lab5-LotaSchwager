#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "treemap.h"

typedef struct TreeNode TreeNode;


struct TreeNode {
    Pair* pair;
    TreeNode * left;
    TreeNode * right;
    TreeNode * parent;
};

struct TreeMap {
    TreeNode * root;
    TreeNode * current;
    int (*lower_than) (void* key1, void* key2);
};

int is_equal(TreeMap* tree, void* key1, void* key2){
    if(tree->lower_than(key1,key2)==0 &&  
        tree->lower_than(key2,key1)==0) return 1;//keys iguales
    else return 0;
}

TreeNode * createTreeNode(void* key, void * value) {
    TreeNode * new = (TreeNode *)malloc(sizeof(TreeNode));
    if (new == NULL) return NULL;
    new->pair = (Pair *)malloc(sizeof(Pair));
    new->pair->key = key;
    new->pair->value = value;
    new->parent = new->left = new->right = NULL;
    return new;
}

TreeMap * createTreeMap(int (*lower_than) (void* key1, void* key2)) {
   TreeMap * map = (TreeMap *)malloc(sizeof(TreeMap));
   map->lower_than = lower_than;
   return map;
}


void insertTreeMap(TreeMap * tree, void* key, void * value) {
  

}

TreeNode * minimum(TreeNode * x){
  TreeNode * aux = x;
  
  if (aux->left == NULL) return aux;
  
  while (aux->left != NULL){
    aux = aux->left;
  }
  return aux;
}


void removeNode(TreeMap * tree, TreeNode* node) {

}

void eraseTreeMap(TreeMap * tree, void* key){
    if (tree == NULL || tree->root == NULL) return;

    if (searchTreeMap(tree, key) == NULL) return;
    TreeNode* node = tree->current;
    removeNode(tree, node);

}




Pair * searchTreeMap(TreeMap * tree, void* key) {
   TreeNode * nodeKey = tree->root;
   
   if (nodeKey == NULL) return NULL;

   if ((is_equal (tree,key,nodeKey->pair->key)) == 1){
     tree->current = nodeKey;
     return nodeKey->pair;
   }
  
   while (nodeKey != NULL){

     if ((is_equal (tree,key,nodeKey->pair->key)) == 1){
      tree->current = nodeKey;
      return nodeKey->pair;
     }

     if (tree->lower_than(key, nodeKey->pair->key) == 1){
       nodeKey = nodeKey->left;
     }
     else{
       nodeKey = nodeKey->right;
     }
     
  }
  return NULL;
}

Pair * upperBound(TreeMap * tree, void* key) {
    return NULL;
}

Pair * firstTreeMap(TreeMap * tree) {
  TreeNode * aux = minimum(tree->root);

  tree->current = aux;
  return aux->pair;

  
}

Pair * nextTreeMap(TreeMap * tree) {
    return NULL;
}
