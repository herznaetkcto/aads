#include "treeProcess.hpp"
#include <functional>

void doroshenko::strToTree(std::string expression, BST< std::string, BST< long long, std::string > >& result)
{
  std::string symbol = "";
  size_t i = 0;
  size_t count = 0;
  std::string name;
  long long key;
  std::string value;
  BST< long long, std::string > dict;
  while (i < expression.length())
  {
    if (expression[i] == ' ')
    {
      i++;
      count++;
      if (count == 1)
      {
        name = symbol;
        if (result.find(name) != result.end())
        {
          dict.clear();
        }
      }
      else if (count % 2 == 0)
      {
        key = std::stoll(symbol);
      }
      else
      {
        value = symbol;
        dict.insert(key, std::ref(value));
      }
      symbol = "";
    }
    else if (i == (expression.length() - 1))
    {
      symbol += expression[i];
      i++;
      value = symbol;
      dict.insert(key, value);
      result.insert(name, std::ref(dict));
      dict.clear();
    }
    else
    {
      symbol += expression[i];
      i++;
    }
  }
}

void doroshenko::inputTree(std::istream& input, BST<std::string, BST<long long, std::string>>& treeOfDicts)
{
  std::string inputLine;
  while (!input.eof())
  {
    std::getline(input, inputLine);
    if (!inputLine.empty())
    {
      strToTree(inputLine, treeOfDicts);
    }
  }
}

void doroshenko::print(BST< std::string, BST< long long, std::string > >& treeOfDicts)
{
  std::string nameOfDict;
  std::cin >> nameOfDict;
  BST< std::string, BST< long long, std::string > >::Iterator iter = treeOfDicts.find(nameOfDict);
  if (iter == treeOfDicts.end())
  {
    std::cout << "<INVALID COMMAND>\n";
    return;
  }
  else if ((iter->second).getSize() == 0)
  {
    std::cout << "<EMPTY>\n";
    return;
  }
  else
  {
    std::cout << iter->first << " ";
    BST< long long, std::string > dict = iter->second;
    size_t curSize = 0;
    size_t sizeOfDict = (*iter).second.getSize();
    for (BST< long long, std::string >::Iterator it = dict.begin(); it != dict.end(); ++it)
    {
      std::cout << it->first << " " << it->second;
      curSize++;
      if (curSize == sizeOfDict)
      {
        std::cout << "\n";
      }
      else
      {
        std::cout << " ";
      }
    }
  }
}

void doroshenko::intersect(BST< std::string, BST< long long, std::string > >& treeOfDicts)
{
  BST< long long, std::string > newDataset;
  std::string newDictName;
  std::string firstDictName;
  std::string secondDictName;
  std::cin >> newDictName >> firstDictName >> secondDictName;
  BST< std::string, BST< long long, std::string > >::Iterator fDictIt = treeOfDicts.find(firstDictName);
  BST< std::string, BST< long long, std::string > >::Iterator sDictIt = treeOfDicts.find(secondDictName);
  if (fDictIt == treeOfDicts.end() || sDictIt == treeOfDicts.end())
  {
    std::cout << "<INVALID COMMAND>\n";
    return;
  }
  for (BST< long long, std::string >::Iterator it = (fDictIt->second).begin(); it != (fDictIt->second).end(); ++it)
  {
    if ((sDictIt->second).find(it->first) != (sDictIt->second).end())
    {
      newDataset.insert(it->first, it->second);
    }
  }
  if (firstDictName == newDictName)
  {
    treeOfDicts.erase(firstDictName);
    treeOfDicts.insert(newDictName, newDataset);
  }
  else if (secondDictName == newDictName)
  {
    treeOfDicts.erase(secondDictName);
    treeOfDicts.insert(newDictName, newDataset);
  }
  else
  {
    treeOfDicts.insert(newDictName, newDataset);
  }
}

void doroshenko::complement(BST< std::string, BST< long long, std::string > >& treeOfDicts)
{
  BST< long long, std::string > newDataset;
  using tree = BST< long long, std::string >;
  std::string newDictName;
  std::string firstDictName;
  std::string secondDictName;
  std::cin >> newDictName >> firstDictName >> secondDictName;
  BST< std::string, BST< long long, std::string > >::Iterator fDictIt = treeOfDicts.find(firstDictName);
  BST< std::string, BST< long long, std::string > >::Iterator sDictIt = treeOfDicts.find(secondDictName);
  if (fDictIt == treeOfDicts.end() || sDictIt == treeOfDicts.end())
  {
    std::cout << "<INVALID COMMAND>\n";
    return;
  }
  for (tree::Iterator fIt = (fDictIt->second).begin(); fIt != (fDictIt->second).end(); ++fIt)
  {
    if ((sDictIt->second).find(fIt->first) == (sDictIt->second).end())
    {
      newDataset.insert(fIt->first, fIt->second);
    }
  }
  if (firstDictName == newDictName)
  {
    treeOfDicts.erase(firstDictName);
    treeOfDicts.insert(newDictName, newDataset);
  }
  else if (secondDictName == newDictName)
  {
    treeOfDicts.erase(secondDictName);
    treeOfDicts.insert(newDictName, newDataset);
  }
  else
  {
    treeOfDicts.insert(newDictName, newDataset);
  }
}

void doroshenko::unify(BST< std::string, BST< long long, std::string > >& treeOfDicts)
{
  BST< long long, std::string > newDataset;
  using tree = BST< long long, std::string >;
  std::string newDictName;
  std::string firstDictName;
  std::string secondDictName;
  std::cin >> newDictName >> firstDictName >> secondDictName;
  BST< std::string, BST< long long, std::string > >::Iterator fDictIt = treeOfDicts.find(firstDictName);
  BST< std::string, BST< long long, std::string > >::Iterator sDictIt = treeOfDicts.find(secondDictName);
  if (fDictIt == treeOfDicts.end() || sDictIt == treeOfDicts.end())
  {
    std::cout << "<INVALID COMMAND>\n";
    return;
  }
  for (tree::Iterator fIt = (fDictIt->second).begin(); fIt != (fDictIt->second).end(); ++fIt)
  {
    if (newDataset.find(fIt->first) == (fDictIt->second).end())
    {
      newDataset.insert(fIt->first, fIt->second);
    }
  }
  for (tree::Iterator sIt = (sDictIt->second).begin(); sIt != (sDictIt->second).end(); ++sIt)
  {
    if (newDataset.find(sIt->first) == (sDictIt->second).end())
    {
      newDataset.insert(sIt->first, sIt->second);
    }
  }
  if (firstDictName == newDictName)
  {
    treeOfDicts.erase(firstDictName);
    treeOfDicts.insert(newDictName, newDataset);
  }
  else if (secondDictName == newDictName)
  {
    treeOfDicts.erase(secondDictName);
    treeOfDicts.insert(newDictName, newDataset);
  }
  else
  {
    treeOfDicts.insert(newDictName, newDataset);
  }
}
