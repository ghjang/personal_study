// refer to the following urls:
//      - https://www.npmjs.com/package/google-translate-api
//      - https://developers.google.com/web/fundamentals/getting-started/primers/promises
//      - https://github.com/tj/co


// for ES6 features
"use strict";

const fs = require('fs');   // file system
const co = require('co');   // for 'generator, yield' async-await idiom
const translate = require('google-translate-api');


if (process.argv.length != 3) {
    console.error("usage: node app.js <text_file_path>");
    return;
}

let txtFilePath = process.argv[2];
if (!fs.existsSync(txtFilePath)) {
    console.error(`file doesn't exist: ${txtFilePath}`);
    return;
}

let txtContents = fs.readFileSync(txtFilePath, 'utf8');
let lines = txtContents.split('\n');

// NOTE: 'yield' seems not to work in an arrow function at the moment.
//       Due to that reason, for-loops are used rather than an arrow function.
co(function *() {
    for (let i = 0; i < lines.length; ++i) {
        let l = lines[i];
        if (-1 == l.search("\\.")) { // if not a paragraph,
            console.log(l);
        } else {
            let sentences = l.split(". ")
                            .map(s => s.trim())
                            .filter(s => s.length != 0)
                            .map((s, i, arr) => {
                                if (arr.length - 1 != i) {
                                    return `${s}.`;
                                }
                                return s;
                            });

            console.log('[=============]');
            
            try {
                let promises = sentences.map(s => {
                    return translate(s, { from: 'en', to: 'ko' });
                });
                for (let j = 0; j < promises.length; ++j) {
                    let r = yield promises[j];
                    console.log(
`[영어]
${sentences[j]}
[한글][완성도:0]
${r.text}
`
                    );
                };
            } catch (err) {
                console.error('exception was thrown: ' + err);
                process.exit(1);
                return;
            }
        }
    }
}).catch(err => {
    console.error('exception was thrown: ' + err);
});
