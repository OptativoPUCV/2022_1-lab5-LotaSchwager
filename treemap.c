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
  TreeNode * aux = tree->root;

  Pair *search = searchTreeMap(tree,key);
  if (search != NULL) return;

  TreeNode *nodo = createTreeNode(key,value);
  while (aux != NULL){
     if (tree->lower_than(key, aux->pair->key) == 1){
       if (aux->left == NULL){     
         nodo->parent = aux;
         aux->left = nodo;
         tree->current = nodo;
         return;
       }
       aux = aux->left;
     }
     else{
       if (aux->right == NULL){
         nodo->parent = aux;
         aux->right = nodo;
         tree->current = nodo;
         return;
       }
       aux = aux->right;
     }

    nodo->parent = aux;
  }  
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
  if (tree == NULL || tree->root == NULL) return;

  //caso 0-1 hijo
  if (node->left == NULL || node->right == NULL){
    //caso de 0 hijos
    if (node->left == NULL && node->right == NULL){
      if (node->parent->left == node){
        node->parent->left = NULL;
      }
      else{
        node->parent->right = NULL;
      }
      free(node);
      return;
    }
    //caso de 1 hijo en la izquierda
    if (node->left != NULL && node->right == NULL){
      if (node == node->parent->left){
        node->parent->left = node->left;
        node->left->parent =node->parent;
        free (node);
        return;
      }
      else{
        node->parent->right = node->left;
        node->left->parent =node->parent;
        free(node);
        return;
      }
    }
      
    // caso de 1 hijo en la derecha
    if (node->left == NULL && node->right != NULL){
      if (node == node->parent->left){
        node->parent->left = node->right;
        node->right->parent =node->parent;
        free (node);
        return;
      }
      else{
        node->parent->right = node->right;
        node->right->parent =node->parent;
        free(node);
        return;
      }
    }
  }

  //caso 2 hijos
  if (node->left != NULL && node->right != NULL){
    TreeNode * son = minimum(node->right);
    node->pair->key = son->pair->key;
    node->pair->value = son->pair->value;
    removeNode(tree,son);
  }
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
  TreeNode *nodo = tree->current;
  if (nodo->right != NULL){
    TreeNode *minimo =  minimum(nodo->right);
    tree->current = minimo;
    return minimo->pair;
  }

  while (nodo != NULL){

    if ((tree->lower_than(nodo->pair->key, nodo->parent->pair->key) == 1)){
      tree->current = nodo->parent;
      return nodo->parent->pair;
    }

    if (nodo->parent == NULL) return NULL;
    nodo = nodo->parent;
  }
  return NULL;
}
