import {
    Avatar,
    Card,
    Col,
    Container,
    Grid,
    Row,
    Text,
} from '@nextui-org/react';
import toast from 'react-hot-toast';
import Particles from 'react-tsparticles';
// import Paho from 'paho-mqtt';
import './App.css';
import ParticleConfig from './data/particlesjs-config.json';
import { default as patterns } from './data/patterns.json';

function App() {
    // const clientId = 'client_id' + Math.floor(Math.random() * 1000000) + 1;
    // const client = new Paho.Client('driver.cloudmqtt.com', 38651, clientId);

    // const doFail = (e) => console.log(e);

    // const onConnect = () => {
    //     console.log('Conexión exitosa');
    //     client.subscribe('dgs_1');
    // };

    // const onMessageArrived = (message) => {
    //     console.log('Un mensaje ha llegado: ' + message.payloadString);
    // };

    // const onConnectionLost = (responseObject) => {
    //     if (responseObject.error !== 0) {
    //         console.log('onConnectionLost: ', responseObject.errorMessage);
    //     }
    // };

    // const command = (value) => {
    //     console.log(value);
    //     const message = new Paho.Message(value + '');
    //     message.destinationName = 'dgs_1';
    //     client.send(message);
    // };

    // client.onConnectionLost = onConnectionLost;
    // client.onMessageArrived = onMessageArrived;

    // const options = {
    //     useSSL: true,
    //     userName: 'clxxwiek',
    //     password: 'PtsiiKX9xhVm',
    //     onSuccess: onConnect,
    //     onFailure: doFail,
    // };

    // client.connect(options);

    const handleClickedCard = (name) => {
        toast.success(name);
    };

    return (
        <div className="background">
            <Particles params={ParticleConfig}></Particles>
            <Container>
                <Row justify="center" align="center">
                    <Text
                        h1
                        color="white"
                        style={{
                            margin: 50,
                            fontWeight: 'lighter',
                            textAlign: 'center',
                        }}
                    >
                        Proyecto Cubo Led
                    </Text>
                </Row>
                <Grid.Container gap={2} justify="center">
                    {patterns.map((pattern, i) => (
                        <Grid xs={6} sm={4} key={i}>
                            <Card
                                width="100%"
                                cover
                                clickable
                                hoverable
                                onClick={() => handleClickedCard(pattern.name)}
                            >
                                <Card.Header
                                    style={{
                                        position: 'absolute',
                                        zIndex: 1,
                                        top: 5,
                                    }}
                                >
                                    <Col>
                                        <Text
                                            size={12}
                                            weight="bold"
                                            transform="uppercase"
                                            color="#ffffffAA"
                                        >
                                            {pattern.description}
                                        </Text>
                                        <Text h4 color="white">
                                            {pattern.name}
                                        </Text>
                                    </Col>
                                </Card.Header>
                                <Card.Image
                                    autoResize={false}
                                    src={pattern.img_url}
                                    height={200}
                                    width="100%"
                                    alt="Card image background"
                                />
                            </Card>
                        </Grid>
                    ))}
                </Grid.Container>

                <div className="center">
                    <p>Done with &#128151; by</p>
                    <Avatar.Group>
                        <Avatar
                            size="large"
                            pointer
                            src="./assets/luis.jpg"
                            bordered
                            color="gradient"
                            stacked
                        />
                        <Avatar
                            size="large"
                            pointer
                            src="./assets/omar.jpg"
                            bordered
                            color="gradient"
                            stacked
                        />
                        <Avatar
                            size="large"
                            pointer
                            src="./assets/daniel.jpg"
                            bordered
                            color="gradient"
                            stacked
                        />
                    </Avatar.Group>
                </div>
            </Container>
        </div>
    );
}

export default App;
