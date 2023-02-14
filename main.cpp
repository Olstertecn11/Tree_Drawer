#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
#include <queue>
#include <iostream>
#include "textNode.cpp"
using namespace std;
#define WIDTH 1070
#define HEIGHT 920
sf::RenderWindow window(sf::VideoMode(1070, 920), "SFML works!");
struct node
{
        int data;
        node *left, *right, *parent; 
        sf::CircleShape shape; 
        sf::RectangleShape leftone;
        sf::RectangleShape rightone; 
	textNode text = textNode("", sf::Color::Red, 26);

}*root;
class Tree
{
public:
        Tree();
        void insert(int, node*, int, int, int, int);
        void Display(node*); 
        void inOrder(node*); 
        void PostOrder(node*); 
        void PreOrder(node*); 
        bool isEmpty(); 
        void Deletion(int); 
        node* SearchNode(int, node*); 
};
bool Tree::isEmpty()
{
        if (!root)
                return true;
        return false; 
}
Tree::Tree() { root = NULL; }
void Tree::insert(int data, node* Node = root, int x = 250, int y = 50, int a = 260, int b = 85)
{
        node* new_node = new node; 
        new_node->shape.setRadius(20);
        new_node->shape.setFillColor(sf::Color::Green);
        new_node->left = new_node->right = new_node->parent = NULL; 
        new_node->data = data; 
        new_node->shape.setPosition(sf::Vector2f(x, y));
	new_node->text.setText(sf::Vector2f(x, y), to_string(new_node->data));
        if (!root)
        {
                root = new_node;
                return; 
        }
        if (data >= Node->data)
        {
                if (Node->right)
                        insert(data, Node->right, x + 50, y + 50, a + 50, b + 50); 
                else
                {
                        Node->right = new_node;
                        new_node->parent = Node; 
                        new_node->shape.setPosition(sf::Vector2f((x + 50), (y + 50))); 
                        new_node->parent->rightone.setSize(sf::Vector2f(50, 5)); 
                        new_node->parent->rightone.setFillColor(sf::Color::Red);
                        new_node->parent->rightone.setRotation(230);
                        new_node->parent->rightone.setPosition(sf::Vector2f(a+50, b+40));
			new_node->text.setText(sf::Vector2f(a+50, b+40), to_string(new_node->data));
                }
        }
        else if (data < Node->data)
        {
                if (Node->left)
                        insert(data, Node->left, x - 50, y + 50, a - 50, b + 50);
                else
                {
                        Node->left = new_node; 
                        new_node->parent = Node; 
                        new_node->shape.setPosition(sf::Vector2f((x - 50), (y + 50)));
                        new_node->parent->leftone.setSize(sf::Vector2f(50, 5));
                        new_node->parent->leftone.setFillColor(sf::Color::Red);
                        new_node->parent->leftone.setRotation(130);
                        new_node->parent->leftone.setPosition(sf::Vector2f(a, b));
			new_node->text.setText(sf::Vector2f(a, b), to_string(new_node->data));
                }
        }
}
void Tree::Display(node* Root = root)
{
        if (!root)
        {
                cout << "Nothing to Display";
                return;
        }
        queue<node*> obj;
        obj.push(Root);
        while (!obj.empty())
        {
                node* temp = obj.front();
                window.draw(temp->shape);
		window.draw(temp->text);
                if (temp->left)
                        window.draw(temp->leftone);
                if (temp->right)
                        window.draw(temp->rightone); 
                //cout << temp->data << " ";
                obj.pop();
                if (temp->left)
                        obj.push(temp->left);
                if (temp->right)
                        obj.push(temp->right);
        }
        window.display();
}

int main()
{
        int n; 
        Tree obj;
        while (window.isOpen())
        {
                cout << "Enter Number to Insert: "; 
                cin >> n;
                obj.insert(n); 
                sf::Event event;
                obj.Display(); 
                while (window.pollEvent(event))
                {
                        if (event.type == sf::Event::Closed)
			{
			  window.close();
			}

			if(event.type == sf::Event::KeyPressed){
			  if(event.key.code == sf::Keyboard::Escape){
			    window.close();
			  }
			}
                }
                window.clear();
        }

        return 0;
}
