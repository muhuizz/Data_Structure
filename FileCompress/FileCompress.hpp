#pragma once 
#include <Windows.h>
#include "HuffmanTree.hpp"
#include <string>

typedef long long Longtype;
struct CharInfo
{
	int _ch;
	Longtype _count;
	string _code;
	CharInfo(Longtype count = 0)
		:_count(count)
		, _ch(0)
	{}
	bool operator!=(const CharInfo& info)const
	{
		return _count != info._count;
	}
	bool operator<(const CharInfo& info)const
	{
		return _count < info._count;
	}
	CharInfo operator+(const CharInfo& info)
	{
		return CharInfo(_count + info._count);
	}
};

class FileCompress
{
public:
	FileCompress()
	{
		for (int i = 0; i < 256; i++)//ch
		{
			_info[i]._ch = i;
			_info[i]._count = 0;
		}
	}

	string Compress(const char* filename)
	{
		string sourcefilename = filename;
		string compressfilename;											//生成压缩文件名
		string configfilename;												//配置文件名
		configfilename = sourcefilename + ".config";
		compressfilename = sourcefilename + ".comp";
 		
		//打开读写文件
		FILE* fout = fopen(filename, "rb");
		assert(fout);
		FILE* fin = fopen(compressfilename.c_str(), "wb");
		assert(fin);
		FILE* finconfig = fopen(configfilename.c_str(), "wb");
		assert(finconfig);

		//统计字符个数count
		int ch = fgetc(fout);
		while (ch != EOF)
		{
			_info[ch]._count++;
			ch = fgetc(fout);
		}

		//生成huffman树
		size_t size = sizeof(_info) / sizeof(_info[0]);
		HuffmanTree<CharInfo> tree(_info, size, CharInfo(0));

		//生成huffman编码code
		string s;
		GetHuffmanCode(tree.GetRoot(), s);

		//压缩文件
		int result = fseek(fout, 0, SEEK_SET);
		int pos = 0;
		int value = 0;
		while ((ch = fgetc(fout)) != EOF)
		{
			string& code = _info[ch]._code;
			for (size_t i = 0; i < code.size(); i++)
			{
				value <<= 1;
				value |= (code[i] - '0');
				pos++;
				if (pos == 8)
				{
					fputc(value, fin);
					pos = 0;
					value = 0;
				}
			}
		}
		if(pos != 0)
		{
			value <<= (8 - pos);
			fputc(value, fin);
		}

		//写入配置文件，配置文件内容为每个字符出现的个数，格式为  char,num\n
		string configfile;
		char arr[128];
		for (size_t i = 0; i < 256;i++)
		{
			if (_info[i]._count != 0)
			{
				//configfile += _info[i]._ch;
				//configfile += ',';
				//configfile += _itoa((int)_info[i]._count, arr, 10);
				//configfile += '\n';
				fputc(_info[i]._ch, finconfig);
				configfile += ',';
				_itoa((int)_info[i]._count, arr, 10);
				configfile += arr;
				configfile += '\n';
				fputs(configfile.c_str(), finconfig);
				configfile.clear();
			}
		}
		fclose(fin);
		fclose(fout);
		fclose(finconfig);
		return compressfilename;
	}

	string Uncompress(const char* filename)
	{
		string uncompressfilename = filename;      // 压缩文件名
		string sourcefilename = filename;              //源文件名
		string configfilename;                                //配置文件名
		
		//生成文件名
		int pos = sourcefilename.rfind('.');
		sourcefilename = sourcefilename.substr(0, pos);		
		configfilename = sourcefilename + ".config";
		pos = sourcefilename.rfind('.');
		string tmp = sourcefilename.substr(pos);
		sourcefilename = sourcefilename.substr(0, pos);
		sourcefilename = sourcefilename + "_uncomp" + tmp;

		//打开文件
		FILE* fin = fopen(sourcefilename.c_str(), "wb");
		assert(fin);
		FILE* fout = fopen(uncompressfilename.c_str(), "rb");
		assert(fout);
		FILE* foutconfig = fopen(configfilename.c_str(), "rb");
		assert(foutconfig);
		
		//重建Huffman树
		string read;
		while (GetLine(foutconfig, read))
		{
			//string 每个字符为char型，一个汉字对应的多个字符一般都大于127，因此需要修正
			int index = read[0];
			if (read[0] < 0)
			{
				index = read[0] + 256;
			}
			_info[index]._count = atoi((read.substr(2)).c_str());
			read.clear();
		}
		size_t size = sizeof(_info) / sizeof(_info[0]);
		HuffmanTree<CharInfo> tree(_info, size, CharInfo(0));
		
		//生成HuffmanTree编码
		string s;
		GetHuffmanCode(tree.GetRoot(), s);

		//解压缩
		size_t value = 0;
		pos = 7;
		HuffmanTreeNode<CharInfo>* root = tree.GetRoot();
		Longtype count = root->_weight._count;
		HuffmanTreeNode<CharInfo>* cur = root;
		size_t ch = fgetc(fout);
		while (ch != EOF)
		{
			pos = 7;
			value = 0;
			while (pos >= 0)
			{
				value = ch & (1 << pos);
				if ((value >> pos) == 1)
					cur = cur->_right;
				else
					cur = cur->_left;
				if (cur->_left == NULL && cur->_right == NULL)
				{
					fputc(cur->_weight._ch, fin);
					count--;
					cur = root;

					if (count == 0)
						break;
				}
				pos--;
			}
			if (count == 0)
				break;
			ch = fgetc(fout);
		}


		fclose(fin);
		fclose(fout);
		fclose(foutconfig);
		return sourcefilename;
	}

protected:
	bool GetLine(FILE* fout,string& s)
	{
		int ch = 0;
		while ((ch = fgetc(fout)) != EOF)
		{
			if ((ch == '\n') && (s.size() != 0))
			{
				return true;
			}
			s += ch;
		}
		return false;
	}
	void GetHuffmanCode(HuffmanTreeNode<CharInfo>* root, string s)
	{
		if (root == NULL)
			return;
		if (root->_left == NULL && root->_right == NULL)
		{
			_info[(root->_weight)._ch]._code = s;
			root->_weight._code = s;
		}
		GetHuffmanCode(root->_left, s+'0');
		GetHuffmanCode(root->_right, s+'1');
	}
protected:
	CharInfo _info[256];
};

void Testcompress()
{
	int begin = GetTickCount();
	FileCompress project;
	//project.Compress("hello1.txt");
	//project.Compress("111.jpg");
	project.Compress("123.mp4");

	int end = GetTickCount();
	cout << "压缩time      " << end - begin << endl;
}
void Testuncompress()
{
	int begin = GetTickCount();
	FileCompress project;
	//project.Uncompress("hello1.txt.comp");
	//project.Uncompress("111.jpg.comp");
	project.Uncompress("123.mp4.comp");

	int end = GetTickCount();
	cout << "解压缩time    " << end - begin << endl;

}