#include "B_tree.h"

void B_Node::borrow_from_left(int node_pos) {
    B_Node* left_sibl = Parent->Children[node_pos - 1];
    int key_sibl = left_sibl->keys[left_sibl->n_keys - 1];
    left_sibl->del_from_leaf(left_sibl->n_keys - 1);
    int key_parent = Parent->keys[node_pos - 1];
    Parent->keys[node_pos - 1] = key_sibl;
    for(int i = 0; i < (n_keys-1); i++) {
        keys[i+1] = keys[i];
    }
    keys[0] = key_parent;
    n_keys++;
}

void B_Node::borrow_from_right(int node_pos) {
    B_Node* right_sibl = Parent->Children[node_pos + 1];
    int key_sibl = right_sibl->keys[0];
    right_sibl->del_from_leaf(0);
    int key_parent = Parent->keys[node_pos];
    Parent->keys[node_pos] = key_sibl;
    keys[n_keys] = key_parent;
    n_keys++;
}

void B_Node::merge_right_sibl(int node_pos) {
    // this в данном случае левый брат на позиции node_pos
    B_Node* right_sibl = Parent->Children[node_pos+1];
    // ключ родителя перекидываем в левого брата (из массива ключей родителя удалим его ниже)
    int key_parent = Parent->keys[node_pos];
    keys[n_keys] = key_parent;
    n_keys++;
    // объединяем левого и правого брата в один узел, перекидываем ключи..
    for (int i = 0; i < right_sibl->n_keys; i++) {
        keys[i + n_keys] = right_sibl->keys[i];
    }
    n_keys += right_sibl->n_keys;
    // удаляем правого брата из массива детей родителя
    for (int i = node_pos+1; i < n_keys; i++) {
        Parent->Children[i] = Parent->Children[i+1];
    }
    // ключ из массива ключей родителя нужно корректно удалить
    Parent->del_from_leaf(node_pos);
    // правый брат больше не нужен
    delete right_sibl;
}

void B_Node::del_from_leaf(int key_pos) {
    // если в узле больше чем минимум ключей (или это корень дерева) - просто удаляем ключ
    if(n_keys > (t - 1) || Parent == nullptr) {
        for(int i = key_pos; i < n_keys - 1; i++) {
            keys[i] = keys[i+1];
        }
        n_keys--;
        return;
    }
    // если в узле минимум ключей, нужно позаимствовать один ключ у брата
    B_Node* left_sibling = nullptr;
    B_Node* right_sibling = nullptr;
    // порядковый номер узла node_del в массиве детей Children
    int node_del_pos = 0;
    while(Parent->Children[node_del_pos] != this) node_del_pos++;
    // если левый брат есть
    if(node_del_pos != 0) {
        left_sibling = Parent->Children[node_del_pos - 1];
        // если у него больше t-1 ключей
        if(left_sibling->n_keys > this->t - 1) {
            // просим у него один ключ ("перебрасываем" через родителя)
            borrow_from_left(node_del_pos);
            key_pos++;
            // теперь в узле больше чем минимум ключей - просто удаляем ключ
            del_from_leaf(key_pos);
            return;
        }
    }
    // если правый брат есть
    if(node_del_pos < (Parent->n_keys)) {
        right_sibling = Parent->Children[node_del_pos + 1];
        // если у него больше t-1 ключей
        if(right_sibling->n_keys > t - 1) {
            // просим у него один ключ ("перебрасываем" через родителя)
            borrow_from_right(node_del_pos);
            // теперь в узле больше чем минимум ключей - просто удаляем ключ
            del_from_leaf(key_pos);
            return;
        }
    }
    // Если у левого и правого брата минимальное количество ключей (просить у них ключ нельзя),
    // то мы объединяем два братских узла
    if(node_del_pos != 0) { // перекидываем все ключи в левого брата из node_del
        key_pos += left_sibling->n_keys;
        left_sibling->merge_right_sibl(node_del_pos - 1);
        left_sibling->del_from_leaf(key_pos);
    } else { // перекидываем ключи с правого брата в node_del
        this->merge_right_sibl(node_del_pos);
        del_from_leaf(key_pos);
    }
}

B_Node* B_Node::get_pred(int key_pos) {
    // максимальный ключ в поддереве левого потомка
    B_Node* cur = Children[key_pos];
    while (cur->leaf == false) {
        cur = cur->Children[cur->n_keys];
    }
    return cur;
}

B_Node* B_Node::get_succ(int key_pos) {
    // минимальный ключ в поддереве правого потомка
    B_Node *cur = Children[key_pos + 1];
    while (cur->leaf == false) {
        cur = cur->Children[0];
    }
    return cur;
}

void B_Node::merge_succ_pred(B_Node *succ, B_Node *pred, int node_pos, int key_pos) {
    if(pred->Parent == succ->Parent) { // если они братья, тогда объединяем их как братьев
        key_pos += pred->n_keys;
        pred->merge_right_sibl(node_pos);
        pred->del_from_leaf(key_pos);
        return;
    }
    // ключ родителя акцессора ставим на место ключа, который удаляем (из массива ключей родителя удалим его ниже)
    int key_succ_parent = succ->Parent->keys[0];
    keys[key_pos] = key_succ_parent;
    // объединяем аксцессор и предецессор в один узел, перекидываем ключи..
    for(int i = 0; i < succ->n_keys; i++) {
        pred->keys[pred->n_keys + 1] = succ->keys[i];
    }
    pred->n_keys += succ->n_keys;
    // удаляем аксцессор из массива детей родителя аксцессора
    for(int i = 0; i < succ->n_keys; i++) {
        succ->Parent->Children[i] = succ->Parent->Children[i + 1];
    }
    // ключ родителя акцессора нужно корректно удалить
    succ->Parent->del_from_leaf(0);
    // аксцессор больше не нужен
    delete succ;
}

void B_Node::del_from_nonleaf(int key_pos) {
    // порядковый номер узла node_del в массиве детей Children
    int node_del_pos = 0;
    if(Parent != nullptr) {
        while(Parent->Children[node_del_pos] != this) node_del_pos++;
    }
    
    B_Node * succ = this->get_succ(key_pos);
    if(succ->n_keys > (t - 1)) { // аксцессор не пустой
        // ключ - аксцессора
        int succ_key = succ->keys[0];
        // ставим аксцессор на место ключа, который мы удаляем;
        this->keys[key_pos] = succ_key;
        // удаляем ключ-аксцессор
        succ->del_from_leaf(0);
        return;
    }
    B_Node * pred = this->get_pred(key_pos);
    if(pred->n_keys > t - 1) { // предецессор не пустой
        // ключ - предецессора
        int pred_key = pred->keys[pred->n_keys-1];
        // ставим предецессор на место ключа, который мы удаляем;
        this->keys[key_pos] = pred_key;
        // удаляем ключ-предецессор
        pred->del_from_leaf(pred->n_keys-1);
        return;
    }
    // аксцессор и предецессор оба пустые
    merge_succ_pred(succ,pred,node_del_pos,key_pos);
}

bool B_Tree::del(int key_to_del) {
    // ищем node_del с ключом key_to_del, который хотим удалить
    B_Node* node_del = search(key_to_del);
    if(node_del == nullptr) {
        std::cout<< "There is no key in the tree";
        return false;
    }
    // порядковый номер ключа key_to_del в массиве ключей keys узла node_del
    int key_pos = 0;
    while(node_del->keys[key_pos] != key_to_del) key_pos++;
    
    if(node_del->leaf == true) { // если узел листовой
        node_del->del_from_leaf(key_pos);
        return true;
    } else { // если узел "внутренний"
        node_del->del_from_nonleaf(key_pos);
        return true;
    }
}
