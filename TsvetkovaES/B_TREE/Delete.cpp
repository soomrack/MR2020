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

void B_Node::merge(int node_pos) {
    if(node_pos != 0) {
        B_Node *left_sibl = Parent->Children[node_pos - 1];
        int key_parent = Parent->keys[node_pos - 1];
        for (int i = n_keys - 1; i >= 0; i--) {
            keys[i + left_sibl->n_keys + 1] = keys[i];
        }
        keys[left_sibl->n_keys] = key_parent;
        for (int i = 0; i < left_sibl->n_keys; i++) {
            keys[i] = left_sibl->keys[i];
        }
        n_keys = n_keys + 1 + left_sibl->n_keys;
        // При объединении ключей количество ключей у родителя может стать меньше минимального.
        // Нужно сделать корректное удаление (просто удаление или удаление с merge или borrow left/right)
        Parent->del_from_leaf(node_pos - 1);
        delete left_sibl; // ????????????????????????????
        return;
    } else {
        B_Node* right_sibl = Parent->Children[node_pos + 1];
        int key_parent = Parent->keys[node_pos];
        keys[n_keys] = key_parent;
        for(int i = 0; i< right_sibl->n_keys; i++) {
            keys[n_keys + i] = right_sibl->keys[i];
        }
        n_keys = n_keys + 1 + right_sibl->n_keys;
        Parent->del_from_leaf(node_pos);
        delete right_sibl;
        return;
    }
    
}

void B_Node::del_from_leaf(int key_count) {
    // если в узле больше чем минимум ключей - просто удаляем ключ
    if(n_keys > (t - 1)) {
        for(int i = key_count; i < n_keys - 1; i++) {
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
            key_count++;
            // теперь в узле больше чем минимум ключей - просто удаляем ключ
            del_from_leaf(key_count);
            return;
        }
    }
    // если правый брат есть
    if(node_del_pos < (Parent->n_keys - 1)) {
        right_sibling = Parent->Children[node_del_pos + 1];
        // если у него больше t-1 ключей
        if(right_sibling->n_keys > t - 1) {
            // просим у него один ключ ("перебрасываем" через родителя)
            borrow_from_right(node_del_pos);
            // теперь в узле больше чем минимум ключей - просто удаляем ключ
            del_from_leaf(key_count);
            return;
        }
    }
    // Если у левого и правого брата минимальное количество ключей (просить у них ключ нельзя),
    // то мы объединяем два братских узла
    merge (node_del_pos);
    // ЗНАЧЕНИЕ key_count изменится!!!!!1
    // удалить ключ из обновлённого узла node_del
    del_from_leaf(key_count);
}

B_Node* B_Node::get_pred(int key_count) {
    // Keep moving to the right most node until we reach a leaf
    B_Node* cur = Children[key_count];
    while (cur->leaf == false) {
        cur = cur->Children[cur->n_keys];
    }
    return cur;
}

B_Node* B_Node::get_succ(int key_count) {
    // Keep moving the left most node starting from Children[key_count+1] until we reach a leaf
    B_Node *cur = Children[key_count+1];
    while (cur->leaf == false) {
        cur = cur->Children[0];
    }
    return cur;
}

void B_Node::del_from_nonleaf(int key_count) {
    /*
    B_Node * succ = this->get_succ();
    if(succ->n_keys > (t - 1)) { // аксцессор не пустой
        // ключ - аксцессор
        int succ_key = succ->keys[0];
        // ставим аксцессор на место ключа, который мы удаляем;
        this->keys[key_count] = succ_key;
        // удаляем ключ-аксцессор
        succ.del_from_leaf(0);
        return;
    }
    Node * pred = this->get_pred();
    if(pred->n_keys > t - 1) { // предецессор не пустой
        // ключ - предецессор
        int pred_key = pred->keys[pred->n_keys-1];
        // ставим предецессор на место ключа, который мы удаляем;
        this->keys[key_count] = pred_key;
        // удаляем ключ-предецессор
        pred.del_from_leaf(pred->n_keys-1);
        return;
    }
    
    // аксцессор и предецессор оба пустые
    int pred_key = pred->keys[pred->n_keys-1];
    // ставим предецессор на место ключа, который мы удаляем;
    this->keys[key_count] = pred_key;
    int a = n_keys-1;
    // объединяем аксцессор и предецессор
    pred.merge(succ);
    // удаляем ключ-предецессор (он в серединке объединённого узла)
    pred.del_from_leaf(a);
    return;
    */
}

bool B_Tree::del(int key_to_del) {
    // ищем node_del с ключом key_to_del, который хотим удалить
    B_Node* node_del = search(key_to_del);
    if(node_del == nullptr) {
        std::cout<< "There is no key in the tree";
        return false;
    }
    // порядковый номер ключа key_to_del в массиве ключей keys узла node_del
    int key_count = 0;
    while(node_del->keys[key_count] != key_to_del) key_count++;
    
    if(node_del->leaf == true) { // если узел листовой
        node_del->del_from_leaf(key_count);
        return true;
    } else { // если узел "внутренний"
        node_del->del_from_nonleaf(key_count);
        return true;
    }
}
