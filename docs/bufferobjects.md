# Buffer Objects
## Character
```
Quick [b]rown-fox
```

## Word 
```
[animal].say(); flush();
```

## Phrase
```
[animal.say](); flush();
```

## Sentence
```
[animal.say();] flush();
```

## Number
```
int value = [12];
int color = [0xFF0000];
int influence = [1.0];
```

## String
```
var a = ['here it is']
var b = ["here it is"]
var c = [`here it is`]
```

## Line
```
let g:nerdtree_always_active=1
[call nerdtree#init]
call nerdtree#toggle()
```

## Paragraph
```
[var c = 1;
var d = 1;
var e = 1;]

var f = 1;
var g = 1;
var h = 1;
```

## Braces
```
Array[<int, 3>] = {1, 2, 3};
Array<int, 3> = [{1, 2, 3}];

shade[(1, 2, 3)];
```

``` 
var array = [[1, 2, 3]];
```

## Block

### Statement
```
[if 1 == 1 {
    doSomething()
}]
```

### Parameter
```
void crazySetter([const String& newName], int newAge);
```

### Function
```
namespace Zoo {
    class Animal {
    public:
        [void setName(const String& newName) {
            name = newName;
        }]
    private:
        String name;
    };
}
```
### Class
```
namespace Zoo {
    [class Animal {
    public:
        void setName(const String& newName) {
            name = newName;
        }
    private:
        String name;
    };]
}
```

### Namespace 
```
[namespace Zoo {
    class Animal {
    public:
        void setName(const String& newName) {
            name = newName;
        }
    private:
        String name;
    };
}]
```

### Tag
#### Attribute
```
<div [class="label-view"] id="nice">
    Mountain Fuji
</div>
```

#### Name
```
<[div] class="label-view" id="nice">
    Mountain Fuji
</div>
```

#### Body
```
<div class="label-view" id="nice">[
    Mountain Fuji
]</div>
```

## Document
```
[select everything in the document]
```
