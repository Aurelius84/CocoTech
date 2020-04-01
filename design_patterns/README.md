## 1.常见的三种最基本的设计模式
1. **创建模式**
   
   > 提供实例化的方法，为适合的情况提供相应的创建方法。
   
2. **结构化模式**

   > 用于处理实体之间的关系，使得这些实体可以更好的协同工作。

3. **行为模式**
   
   > 用于不同的实体进行通信，为实体之间的通信提供更容易、更灵活的通信方法。

## 2.详细的模式介绍
### 2.1 创建型

#### 1. Factory Method (工厂方法)

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

#### 2. Abstract Factory (抽象工厂)

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
#### 3. Builder (建造者)

![Factory Method](https://raw.githubusercontent.com/Aurelius84/CocoTech/master/design_patterns/img/builder.jpeg)

1. **作用**
    > 将一个复杂对象的**构建**与它的**表示**分离开来，使得同样的构建过程可以创建不同的表示。


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


#### 4. Prototype (原型)

![Factory Method](https://raw.githubusercontent.com/Aurelius84/CocoTech/master/design_patterns/img/prototype.jpeg)

1. **作用**
    > 使用原型实例来创建对象，并通过copy这些原型来创建新的对象。

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

#### 5. Singleton (单例)

![Factory Method](https://raw.githubusercontent.com/Aurelius84/CocoTech/master/design_patterns/img/singleton.jpeg)

1. **作用**
    > 保证一个类只有一个实例存在

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

### 2.2 结构型

#### 6. Adapter Class/Object (适配器)

![Factory Method](https://raw.githubusercontent.com/Aurelius84/CocoTech/master/design_patterns/img/adapter_class.jpeg)

1. **作用**
    > 将一个类的接口转换为client想要的另一个接口。Adapter模式使得原本由于接口不兼容而无法一起协作的类，可以重新协作。

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
   
#### 7. Bridge (桥接)

![Factory Method](https://raw.githubusercontent.com/Aurelius84/CocoTech/master/design_patterns/img/bridge.jpeg)

1. **作用**
    > 将抽象的部分与其实现部分分离，使它们均可以独立的变化

2. **适用场景**

    - 试图解耦抽象与实现部分。
    - 类的抽象以及它的实现都可以通过生成子类的方法进行扩充。
    - 对一个抽象的实现部分进行修改，应对client不产生影响，即client不需要重新编译。

3. **样例Demo**
    ```python
    # ConcreteImplementor
    class DrawingApi1(object):
    
        def draw_circle(self, x, y, radius):
    
            print("Api_1.circle at {}:{} radius {}".format(x, y, radius))
    
    # ConcreteImplementor
    class DrawingApi2(object):
    
        def draw_circle(self, x, y, radius):
    
            print("Api_1.circle at {}:{} radius {}".format(x, y, radius))
    
    
    # Abstraction
    class CircleShape(object):
        def __init__(self, x, y, radius, drawing_api):
            self._x = x
            self._y = y
            self._radius = radius
            self._drawing_api = drawing_api
    
        # low level, i.e. implementation
        def draw(self):
            self._drawing_api.draw_circle(self._x, self._y, self._radius)
    
        # high level i.e. Abstraction
        def scale(self, pct):
            self._radius *= pct
    
    
    def main():
        shapes = (
            CircleShape(1, 2, 3, DrawingApi1()),
            CircleShape(5, 7, 11, DrawingApi2())
        )
        
        for shape in shapes:
            shape.scale(2.5)
            shape.draw()
    
    if __name__ == '__main__':
        main()
    ```
  
#### 8. Composite(组合)

![Composite](https://raw.githubusercontent.com/Aurelius84/CocoTech/master/design_patterns/img/composite.jpeg)

1. **作用**
    > 将object组合成**树形**结构，以表示**部分-整体**的层次结构，使得client对单个对象和组合对象的使用，更具有一致性。

2. **适用场景**

    - 对部分-整体层次结构有需要
    - 希望client忽略组合对象和单个对象的不同，统一使用组合结构的岁哦有对象

3. **样例Demo**

    ```python
    # Abstraction
    class Component(object):
        def __init__(self, name):
            self._name = name
    
        def add(self, com):
            pass
    
        def display(self, depth):
            pass
    # Instance
    class Leaf(Component):
        def add(self, com):
            print("leaf can not add")
    
        def display(self, depth):
            name = "-" * depth
            name += self._name
            print(name)
    
    
    class Composite(Component):
        def __init__(self, name):
            super(Composite).__init__(name)
            self.entities = []
    
        def add(self, entity):
            self.entities.append(entity)
        
        def display(self, depth):
            name = "-" * depth
            name += self._name
            for entity in self.entities:
                entity.display(depth+2)
    
    
    if __name__ == "__main__":
        p = Composite("Wong")
        p.add(Leaf("Lee"))
        p.add(Leaf("Zhao"))
        p1 = Composite("Wu")
        p1.add(Leaf("San"))
        p.add(p1)
        p.display(1)
    ```
   
#### 9. Decorator(装饰器)

![Decorator](https://raw.githubusercontent.com/Aurelius84/CocoTech/master/design_patterns/img/decorator.jpeg)

1. **作用**
    > 动态地给一个对象添加一些额外功能。从用法上，装饰器模式比生成子类的方式更加灵活。

2. **适用场景**

    - 在不影响其他对象的情况下，以动态、透明的方式给单个对象添加职责
    - 处理可撤销的职责
    - 无法采用生成子类的方法进行扩充的情况:
        - 可能存在大量独立的扩展，为支持每一种组合，将会产生大量的子类，子类数目爆炸增长
        - 类定义可能被隐藏，或类定义不能用于生成子类

3. **样例Demo**

    ```python
    class Foo(object):
        def func1(self):
            print("original func1")
    
        def func2(self):
            print("original func2")
    
    class FooDecorator(object):
        def __init__(self, decorator):
            self._decorator = decorator
    
        def func1(self):
            print("decorated func1")
            self._decorator.func1()
    
        def __getattr__(self, item):
            return getattr(self._decorator, item)
    
    
    if __name__ == '__main__':
        foo = Foo()
        foo_decorator = FooDecorator(foo)
        foo_decorator.func1()
        foo_decorator.func2()
    ```

#### 10. Facade (外观)

![Facade](https://raw.githubusercontent.com/Aurelius84/CocoTech/master/design_patterns/img/facade.jpeg)

1. **作用**
    > 为子系统的一组接口提供一个一致的界面，Facade模式定义了一个高层接口，使得子系统更加容易使用。

2. **适用场景**

    - 当子系统因不断演化而变得复杂，试图为复杂子系统提供一个简单的接口
    - 大多数模式使用时会产生更多更小的类，试图重用子类，或对子系统进行定制
    - client端与抽象类的实现部分之间存在很大的依赖性，引入Facade可以将子系统与client和其他子系统分离，提高子系统的独立性和可移植性
    - 当需构建一个层次结构的子系统时，使用Facade模式定义子系统的每层的入口点
        - 若子系统之间相互依赖，可借助Facade进行通讯，简化它们之间的依赖关系

3. **样例Demo**

    ```python
    import time
    
    SLEEP = 0.5
    
    class TC1(object):
        def run(self):
            print("###### In Test 1 ######")
            time.sleep(SLEEP)
            print("Setting up")
            time.sleep(SLEEP)
            print("Running test")
            time.sleep(SLEEP)
            print("Tearing down")
            time.sleep(SLEEP)
            print("Test 1 Finished")
    
    class TC2(object):
        def run(self):
            print("###### In Test 2 ######")
            time.sleep(SLEEP)
            print("Setting up")
            time.sleep(SLEEP)
            print("Running test")
            time.sleep(SLEEP)
            print("Tearing down")
            time.sleep(SLEEP)
            print("Test 2 Finished")
    
    class TC3(object):
        def run(self):
            print("###### In Test 3 ######")
            time.sleep(SLEEP)
            print("Setting up")
            time.sleep(SLEEP)
            print("Running test")
            time.sleep(SLEEP)
            print("Tearing down")
            time.sleep(SLEEP)
            print("Test 3 Finished")
    
    # Facade
    class TestRunner(object):
        def __init__(self):
            self.tc1 = TC1()
            self.tc2 = TC2()
            self.tc3 = TC3()
            self.tests = [i for i in (self.tc1, self.tc2, self.tc3)]
            
        def run_all(self):
            for test in self.tests:
                test.run()
    
    
    # Client
    if __name__ == '__main__':
        test_runner = TestRunner()
        test_runner.run_all()
    ```