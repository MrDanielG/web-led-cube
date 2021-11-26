import Paho from 'paho-mqtt';
import './App.css';
import logo from './logo.svg';

function App() {
    const clientId = 'client_id' + Math.floor(Math.random() * 1000000) + 1;
    const client = new Paho.Client('driver.cloudmqtt.com', 38651, clientId);

    const doFail = (e) => console.log(e);

    const onConnect = () => {
        console.log('Conexión exitosa');
        client.subscribe('dgs_1');
    };

    const onMessageArrived = (message) => {
        console.log('Un mensaje ha llegado: ' + message.payloadString);
    };

    const onConnectionLost = (responseObject) => {
        if (responseObject.error !== 0) {
            console.log('onConnectionLost: ', responseObject.errorMessage);
        }
    };

    const command = (value) => {
        console.log(value);
        const message = new Paho.Message(value + '');
        message.destinationName = 'dgs_1';
        client.send(message);
    };

    client.onConnectionLost = onConnectionLost;
    client.onMessageArrived = onMessageArrived;

    const options = {
        useSSL: true,
        userName: 'clxxwiek',
        password: 'PtsiiKX9xhVm',
        onSuccess: onConnect,
        onFailure: doFail,
    };

    client.connect(options);

    return (
        <div className="App">
            <header className="App-header">
                <img src={logo} className="App-logo" alt="logo" />
                <p>
                    Edit <code>src/App.js</code> and save to reload.
                </p>
                <a
                    className="App-link"
                    href="https://reactjs.org"
                    target="_blank"
                    rel="noopener noreferrer"
                >
                    Learn React
                </a>
                <button onClick={() => command(0)}>0</button>
                <button onClick={() => command(1)}>1</button>
            </header>
        </div>
    );
}

export default App;
