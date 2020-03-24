## 1.常见的三种最基本的设计模式
1. **创建模式**
   
   提供实例化的方法，为适合的情况提供相应的创建方法。
   
2. **结构化模式**

   用于处理实体之间的关系，使得这些实体可以更好的协同工作。

3. **行为模式**
   
   用于不同的实体进行通信，为实体之间的通信提供更容易、更灵活的同你方法。

## 2.详细的模式介绍
### 2.1 创建型

#### Factory Method (工厂方法)

![Factory Method](https://raw.githubusercontent.com/Aurelius84/CocoTech/master/design_patterns/img/factory_method.jpeg)

1. **作用**
    > 定义一个用于创建对象的接口，让子类决定应该实例化哪一个类。Factory Method 使一个类的实例化延迟到其子类。

2. **适用场景**
    - 当一个类不知道它所必须创建的对象的类的时候。
    - 当一个类希望由它的子类来指定它所创建的对象的时候。

3. **样例Demo**
    ```python
    class ChinaGetter(object):
        def __init__(self):
            self.trans = dict(dog='小狗',cat='小猫')

        def get(self, msg_id):
            try:
                return self.trans[msg_id]
            except KeyError:
                return str(msg_id)

    class EnglishGetter(object):
        def get(self, msg_id):
            return str(msg_id)

    def get_localizer(language='English'):
        languages = dict(English=EnglishGetter, China=ChinaGetter)
        return languages[language]()

    # create localizer
    e, g = get_localizer('English'), get_localizer('China')
    for text in "A cat sits on the desk".split():
        print(e.get(text), g.get(text))
    ```

#### Abstract Factory (抽象工厂)

1. **作用**
    > 提供一个创建相关或者相互依赖对象的接口，而无需指定它们具体的类。

2. **适用场景**
    - 当一个系统独立与它的产品的创建、组合和表示时
    - 当一个系统需要多个产品系列中的一个来配置时
    - 当强调一系列相关的产品对象的设计以便进行联合使用时
    - 当提供一个产品类库，而只想显示它们的接口而不是实现时。

3. **样例Demo**
    ```python
    import random

    class Cat(object):
        def speak(self):
            return 'meow'

        def __str__(self):
            return 'Cat'

    class Dog(object):
        def speak(self):
            return 'woolf'

        def __str__(self):
            return 'Dog'

    class CatFactory(object):
        def get_pet(self):
            return Cat()

        def get_food(self):
            return 'Cat food'

    class DogFactory(object):
        def get_pet(self):
            return Dog()

        def get_food(self):
            return 'Dog food'

    class PetShop(object):
        def __init__(self, animal_factory=None):
            self.factory = animal_factory

        def show_pet(self):
            pet = self.factory.get_pet()
            print('This is a lovely ', str(pet))
            print('pet speaks ', pet.speak())
            print('pet eats ', pet.get_food())

    def get_factory():
        return random.choice([DogFactory, CatFactory])
    ```
#### Builder (建造者)

![Factory Method](https://raw.githubusercontent.com/Aurelius84/CocoTech/master/design_patterns/img/builder.jpeg)

1. **作用**

    将一个复杂对象的**构建**与它的**表示**分离开来，使得同样的构建过程可以创建不同的表示。


2. **适用场景**

    - 当一个复杂对象的创建独立与组成此对象的子部件，以及子部件的装配方式时
    - 允许由不同的构造过程创建不同的对象时

3. **样例Demo**
    ```python
   class Director(object):
       def __init__(self):
           self.builder = None
   
       def construct_building(self):
           self.builder.new_building()
           self.builder.build_floor()
           self.builder.build_size()
       
       def get_building(self):
           return self.builder.new_building
       
   class Builder(object):
       def __init__(self):
           self.building = None
       
       def new_building(self):
           self.building = Building()
   
       
   class BuilderHouse(Builder):
       def build_floor(self):
           self.building.floor = "One"
       
       def build_size(self):
           self.building.size = "Big"
   
   class BuilderFlat(Builder):
       def build_floor(self):
           self.building.floor = "Two"

       def build_size(self):
           self.building.size = "Small"   
   
   class Building(object):
       def __init__(self):
           self.floor = None
           self.size = None
   
       def __repr__(self):
           return "Floor : %s | Size: %s" % (self.floor, self.size)
   
   if __name__ == '__main__':
       director = Director()
       director.builder = BuilderHouse()
       director.construct_building()
       building = director.get_building()
       print(building)
       director.builder = BuilderFlat()
       director.construct_building()
       building = director.get_building()
       print(building)   
   ```


#### Prototype (原型)

![Factory Method](https://raw.githubusercontent.com/Aurelius84/CocoTech/master/design_patterns/img/prototype.jpeg)

1. **作用**

    使用原型实例来创建对象，并通过copy这些原型来创建新的对象。

2. **适用场景**

    - 动态装载，即当要实例化的类在运行时才指定
    - 为避免创建一个与产品类层次平行的工厂类层次时
    - 当一个类的实例只能又几个不同状态组合的一种时
    
    建议相应数目的原型，并clone它们，比每次用合适的状态手工实例化，要更方便一些。

3. **样例Demo**
    ```python
    import copy
   
    class Prototype:
        def __init__(self):
            self._objects = {}
    
        def register_object(self, name, obj):
            self._objects[name] = obj
    
        def unregister_object(self, name):
            del self._objects[name]
    
        def clone(self, name, **attr):
            obj = copy.deepcopy(self._objects.get(name))
            obj.__dict__.update(attr)
            return obj
    
    def main():
        class A:
            def __str__(self):
                return "I"'m A.'
        
        a = A()
        prototype = Prototype()
        prototype.register_object('a', a)
        b = prototype.clone('a', a=1, b=2, c=3)
    
        print(a)
        print(b.a, b.b, b.c)
    
    if __name__ == '__main__':
        main()
    ```

#### Singleton (单例)

![Factory Method](https://raw.githubusercontent.com/Aurelius84/CocoTech/master/design_patterns/img/singleton.jpeg)

1. **作用**

    保证一个类只有一个实例存在

2. **适用场景**

    - 当类只允许存在一个实例，且client可以从一个全局变量访问它
    - 当这个唯一实例可以通过子类扩展，且client无需更改代码就能使用一个扩展的实例

3. **样例Demo**
    ```python
    class Singleton(object):
        def __new__(cls, *args, **kwargs):
            if not hasattr(cls, '_instance'):
                org = super(Singleton, cls)
                cls._instance = org.__new__(cls, *args, **kwargs)
            return cls._instance
    
    class SingleSpam(Singleton):
        def __init__(self, s):
            self.s = s
        
        def __str__(self):
            return self.s
    
    if __name__ == '__main__':
        spam = SingleSpam('spam')
        print(id(spam), spam)
    
        spa = SingleSpam('spa')
        print(id(spa), spa)
        print(id(spam), spam)
    ```

### 2.1 创建型

#### Factory Method (工厂方法)

![Factory Method](https://raw.githubusercontent.com/Aurelius84/CocoTech/master/design_patterns/img/adapter_class.jpeg)

1. **作用**

    将一个类的接口转换为client想要的另一个接口。Adapter模式使得原本由于接口不兼容而无法一起协作的类，可以重新协作。

2. **适用场景**

    - 试图使用一个已经存在的但接口不符合你需求的类
    - 试图创建一个可复用的类，此类可以与其他不相关的类或不可预见的类协同工作
    - 试图使用已存在的子类，但无法对每一个都进行子类话以匹配他们的接口。

3. **样例Demo**
    ```python
    import os
    
    class Dog(object):
        def __init__(self):
            self.name = "Dog"
    
        def bark(self):
            return "woof"
    
    class Cat(object):
        def __init__(self):
            self.name = "Cat"
    
        def meow(self):
            return "meow"
    
    class Human(object):
        def __init__(self):
            self.name = "Human"
    
        def speak(self):
            return "hello"
    
    class Car(object):
        def __init__(self):
            self.name = "Car"
    
        def make_noise(self, octane_level):
            return "vroom" % ("!" * octane_level)
    
    
    class Adapter(object):
        def __init__(self, obj, adapted_methods):
            self.obj = obj
            self.__dict__.update(adapted_methods)
    
        def __getattr__(self, item):
            return getattr(self.obj, attr)
    
    
    def main():
        objects = []
        dog = Dog()
        objects.append(Adapter(dog, dict(make_noise=dog.bark)))
        cat = Cat()
        objects.append(Adapter(cat, dict(make_noise=cat.meow)))
        human = Human()
        objects.append(Adapter(human, dict(make_noise=human.speak)))
        car = Car()
        car_noise = lambda: car.make_noise(3)
        objects.append(Adapter(car, dict(make_noise=car_noise)))
    
        for obj in objects:
            print("{0} said {1}".format(obj.name, obj.make_noise()))
    
    if __name__ == "__main__":
        main()
    ```