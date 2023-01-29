# Buffer Objects
## Selection Anchors

### Object
```
[void say(string type) {
    if (type == "cat") {
        print("meow")
    }

    print("sup")
}]
```

### Begining of Object
```
[v]oid say(string type) {
    if (type == "cat") {
        print("meow")
    }

    print("sup")
}
```

### End of Object
```
void say(string type) {
    if (type == "cat") {
        print("meow")
    }

    print("sup")
[}]
```

### Inner Object 
```
void say(string type) {
    [if (type == "cat") {
        print("meow")
    }

    print("sup")]
}
```

### Begining of Inner Object
```
void say(string type) {
    [i]f (type == "cat") {
        print("meow")
    }

    print("sup")
}
```

### End of Inner Object
```
void say(string type) {
    if (type == "cat") {
        print("meow")
    }

    print("sup"[)]
}
```

## Character
```
Quick [b]rown-fox. Jumps over the lazy dog.
```

## Word 
With set of `a-z`, `A-Z`, or `0-9`.
```
Quick [brown]-fox. Jumps over the lazy dog.
```

## Sentence
Ends with `,`, `.`, `;`, `:`, `!`, `?`, `=`, `(`, `{`, `<`, or `[`.

```
[Quick brown-fox.] Jumps over the lazy dog.
```

``` 
class Person
{
    [virtual void Move(]int newAge, int newPostalCode) 
    {
        int age = newAge;
        int postalCode = newPostalCode;
    }
}
```

## Inner Sentence
```
[Quick brown-fox]. Jumps over the lazy dog.
```

``` 
class Person
{
    [virtual void Move](int newAge, int newPostalCode) 
    {
        int age = newAge;
        int postalCode = newPostalCode;
    }
}
```

## Line
```
[Quick brown-fox. Jumps over the lazy dog.]
```

## Paragraph
```
[Tears are a clear liquid secreted by the lacrimal glands (tear gland) found in the eyes of all land mammals. 
Tears are made up of water, electrolytes, proteins, lipids, and mucins that form layers on the surface of eyes. 
    The different types of tears—basal, reflex, and emotional—vary significantly in composition.
    The functions of tears include lubricating the eyes (basal tears), removing irritants (reflex tears), and also aiding the immune system. 
Tears also occur as a part of the body's natural pain response.]

Emotional secretion of tears may serve a biological function by excreting stress-inducing hormones built up through times of emotional distress. 
Tears have symbolic significance among humans.
```

## Indentation
```
Tears are a clear liquid secreted by the lacrimal glands (tear gland) found in the eyes of all land mammals. 
Tears are made up of water, electrolytes, proteins, lipids, and mucins that form layers on the surface of eyes. 
    [The different types of tears—basal, reflex, and emotional—vary significantly in composition.
    The functions of tears include lubricating the eyes (basal tears), removing irritants (reflex tears), and also aiding the immune system.]
Tears also occur as a part of the body's natural pain response.

Emotional secretion of tears may serve a biological function by excreting stress-inducing hormones built up through times of emotional distress. 
Tears have symbolic significance among humans.
```

## Number 
```
Descent from the Cross, c. [1435] by Rogier van der Weyden, the tears of Mary of Clopas
```
```
var a = [12]
var b = [12.3]
var c = [0xFFFFFF]
var d = [0b1011]
var e = [0o777]
```

## Quotes 
```
Carol said ["Go ahead."]
Charlie said ['Go ahead.']
Megan said [`Go ahead.`]
```

## Inner Quotes 
```
Carol said "[Go ahead.]"
Charlie said '[Go ahead.]'
Megan said `[Go ahead.]`
```

## Braces 
```
The meeting will be held next year [(in March)].
3 [{1 + 2}]
I grew up in Sacremento [[Sacramento]] in the 1960s.
[<some.email@mail.com>]
```

## Inner Braces 
```
The meeting will be held next year ([in March]).
3 {[1 + 2]}
I grew up in Sacremento [[Sacramento]] in the 1960s.
<[some.email@mail.com]>
```

## Document
```
[select everything in the buffer.]
```

## C Families

### Comment
```
[// Warning!]

[/* 
This page has make a grown man mad
by the intricate template meta programming
*/]
```

### Inner Comment
```
// [Warning!]

/* 
[This page has make a grown man mad
by the intricate template meta programming]
*/
```

### Statement
```
[if (1 == 1) {
    doSomething();
}]

[switch (type) {
    case 1: doOne(); break;
    case 2: doTwo(); break;
}]
```

### Inner Statement
```
if (1 == 1) {
    [doSomething();]
}

switch (type) {
    [case 1: doOne(); break;
    case 2: doTwo(); break;]
}
```

### Argument
```
void set([const String& newName], int newValue);
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

### Inner Function
```
namespace Zoo {
    class Animal {
    public:
        void setName(const String& newName) {
            [name = newName;]
        }
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

### Class
```
namespace Zoo {
    class Animal {
    [public:
        void setName(const String& newName) {
            name = newName;
        }
    private:
        String name;]
    };
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

### Inner Namespace
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

## XML Families
### Tag 
```
[<div class="label-view" id="nice">
    Mountain Fuji
</div>]
```

### Inner Tag 
```
<div class="label-view" id="nice">
    [Mountain Fuji]
</div>
```

### Attribute 
```
<div [class="label-view"] id="nice">
    Mountain Fuji
</div>
```

## Git 
### Hunk
```
[+ Hello
+ Darkness
+ My]
Old 
Friend
```
