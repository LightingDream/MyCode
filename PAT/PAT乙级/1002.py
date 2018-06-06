
map = {
  1:'yi', 2:'er', 3:'san',
  4:'si', 5:'wu', 6:'liu',
  7:'qi', 8:'ba', 9:'jiu',
  0:'ling'
}

def out(x):
  cur = x % 10
  x = x // 10
  if x > 0:
      out(x)
      print('', str(map[cur]), end='')
  else:
      print(str(map[cur]), end='')

if __name__ == '__main__':
    num = input()
    res = 0
    for ch in num:
        res = res + int(ch)
    out(res)
    print('')
    
