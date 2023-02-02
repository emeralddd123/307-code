const a = [1,2,3,4,5,6,7,8,9]
const [b,c, ...rest] = a

console.log(a)
console.log(b)
console.log(c)
console.log(rest)

const obj = { a: 1, b: 2 };
const { a, b } = obj;
